#include <stdio.h>
#include <windows.h>
#include <time.h>

typedef struct {
    int matriz[10][10];
} MatrizResultado;

// Definición de semáforos
HANDLE semaforo_suma, semaforo_resta, semaforo_multiplicacion;

int main()
{
    double total_time;
    clock_t start, end;
    start = clock();

    HANDLE hMapFile[3];  // Arreglo de handles para las secciones de memoria compartida
    MatrizResultado* pMatrizResultado[3];  // Arreglo de punteros a las estructuras

    // Creamos las secciones de memoria compartida
    for (int i = 0; i < 3; ++i) {
        char sectionName[50];
        sprintf(sectionName, "MatrizSharedMemory%d", i);
        hMapFile[i] = CreateFileMapping(
            INVALID_HANDLE_VALUE,    // Usa el archivo de paginación de la memoria del sistema
            NULL,                    // Security attributes
            PAGE_READWRITE,          // Permisos de lectura y escritura
            0,                       // Tamaño del mapa (0 indica el tamaño de la estructura)
            sizeof(MatrizResultado), // Tamaño de la estructura
            sectionName);            // Nombre de la sección de memoria compartida

        if (hMapFile[i] == NULL) {
            printf("Fallo al crear la seccion de memoria compartida %d (%d)\n", i, GetLastError());
            return 1;
        }

        // Asignamos la estructura a la memoria compartida
        pMatrizResultado[i] = (MatrizResultado*)MapViewOfFile(
            hMapFile[i],          // Handle de la sección de memoria compartida
            FILE_MAP_ALL_ACCESS,  // Permisos de lectura y escritura
            0,
            0,
            sizeof(MatrizResultado));

        if (pMatrizResultado[i] == NULL) {
            printf("Fallo al asignar la memoria compartida %d (%d)\n", i, GetLastError());
            CloseHandle(hMapFile[i]);
            return 1;
        }
    }

    // Inicialización de semáforos
    semaforo_suma = CreateSemaphore(NULL, 1, 1, "SemSuma");
    semaforo_resta = CreateSemaphore(NULL, 1, 1, "SemResta");
    semaforo_multiplicacion = CreateSemaphore(NULL, 1, 1, "SemMultiplicacion");

    if (semaforo_suma == NULL || semaforo_resta == NULL || semaforo_multiplicacion == NULL) {
        printf("Fallo al crear semáforos (%d)\n", GetLastError());
        return 1;
    }

    // Lanzamos los procesos hijos para realizar las operaciones
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Llamar a los programas correspondientes con su semáforo respectivo
    //Suma
    si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE); // Redirigir la salida estándar
    if (!CreateProcess(NULL, ".\\suma.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        printf("Fallo al invocar CreateProcess para suma.exe (%d)\n", GetLastError());
        return 1;
    }
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    //Resta
    si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE); // Redirigir la salida estándar
    if (!CreateProcess(NULL, ".\\resta.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        printf("Fallo al invocar CreateProcess para resta.exe (%d)\n", GetLastError());
        return 1;
    }
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    //Multiplicacion
    si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE); // Redirigir la salida estándar
    if (!CreateProcess(NULL, ".\\multiplicacion.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        printf("Fallo al invocar CreateProcess para multiplicacion.exe (%d)\n", GetLastError());
        return 1;
    }
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    //Traspuesta
    si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE); // Redirigir la salida estándar
    if (!CreateProcess(NULL, ".\\traspuesta.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        printf("Fallo al invocar CreateProcess para traspuesta.exe (%d)\n", GetLastError());
        return 1;
    }
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    //inversa
    si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE); // Redirigir la salida estándar
    if (!CreateProcess(NULL, ".\\inversa.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        printf("Fallo al invocar CreateProcess para inversa.exe (%d)\n", GetLastError());
        return 1;
    }
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    // Liberamos recursos
    for (int i = 0; i < 3; ++i) {
        UnmapViewOfFile(pMatrizResultado[i]);
        CloseHandle(hMapFile[i]);
    }

    // Cerrar semáforos
    CloseHandle(semaforo_suma);
    CloseHandle(semaforo_resta);
    CloseHandle(semaforo_multiplicacion);

    end = clock();
    total_time = ((double)((end - start))) / CLOCKS_PER_SEC;

    // Llamar al programa para imprimir los resultados
    system(".\\imprimir.exe");

    printf("\n\t----Tiempo de ejecucion fue de: %f\n", total_time);
    return 0;
}
