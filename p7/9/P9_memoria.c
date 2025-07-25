#include <stdio.h>
#include <windows.h>
#include <time.h>

typedef struct {
    int matriz[10][10];
} MatrizResultado;

int main()
{
    double total_time;
    clock_t start, end;
    start = clock();

    HANDLE hMapFile;
    MatrizResultado* pMatrizResultado;

    // Creamos la sección de memoria compartida
    hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,    // Usa el archivo de paginación de la memoria del sistema
        NULL,                    // Security attributes
        PAGE_READWRITE,          // Permisos de lectura y escritura
        0,                       // Tamaño del mapa (0 indica el tamaño de la estructura)
        sizeof(MatrizResultado), // Tamaño de la estructura
        "MatrizSharedMemory");   // Nombre de la sección de memoria compartida

    if (hMapFile == NULL) {
        printf("Fallo al crear la seccion de memoria compartida (%d)\n", GetLastError());
        return 1;
    }

    // Asignamos la estructura a la memoria compartida
    pMatrizResultado = (MatrizResultado*)MapViewOfFile(
        hMapFile,          // Handle de la sección de memoria compartida
        FILE_MAP_ALL_ACCESS, // Permisos de lectura y escritura
        0,
        0,
        sizeof(MatrizResultado));

    if (pMatrizResultado == NULL) {
        printf("Fallo al asignar la memoria compartida (%d)\n", GetLastError());
        CloseHandle(hMapFile);
        return 1;
    }

    // Lanzamos los procesos hijos para realizar las operaciones
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (!CreateProcess(NULL, ".\\suma.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        printf("Fallo al invocar CreateProcess para suma.exe (%d)\n", GetLastError());
        return 1;
    }
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    if (!CreateProcess(NULL, ".\\resta.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        printf("Fallo al invocar CreateProcess para resta.exe (%d)\n", GetLastError());
        return 1;
    }
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    if (!CreateProcess(NULL, ".\\multiplicacion.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        printf("Fallo al invocar CreateProcess para multiplicacion.exe (%d)\n", GetLastError());
        return 1;
    }
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    if (!CreateProcess(NULL, ".\\inversa.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        printf("Fallo al invocar CreateProcess para inversa.exe (%d)\n", GetLastError());
        return 1;
    }
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    if (!CreateProcess(NULL, ".\\traspuesta.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        printf("Fallo al invocar CreateProcess para traspuesta.exe (%d)\n", GetLastError());
        return 1;
    }
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    // Liberamos la memoria compartida
    UnmapViewOfFile(pMatrizResultado);
    CloseHandle(hMapFile);

    end = clock();
    total_time = ((double)((end - start))) / CLOCKS_PER_SEC;

    system(".\\imprimir.exe");

    printf("\n\t----Tiempo de ejecucion fue de: %f\n", total_time);
    return 0;
}
