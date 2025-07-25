#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

#include "main.h"
#include "./inputs/inputs.h"
#include "copyFiles.h"

static const char *menuText = 
"Acciones:\n"
	"\t1. Copiar archivos\n"
	"\t2. Visualizar un archivo\n"
	"\t3. Salir\n"
"opcion: "
;

void menuCopyorView(){
    int opcion;

    checkIntPosValue(menuText, &opcion);
    switch (opcion) {
        case 1:
            Copy();
            break;
        case 2:
            View();
            break;
        case 3:
            break;
        default:
            printf("Opción inválida.\n");
            menuCopyorView();
            return;
    }
}

void View() {
    char ruta[MAX_PATH];

    checkStrValue("Ingrese la ruta del archivo a visualizar: ", ruta, MAX_PATH);
    HANDLE hFile = CreateFile(ruta, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        printf("Error al abrir el archivo\n");
        return;
    }

    // tamaño del archivo
    DWORD fileSize = GetFileSize(hFile, NULL);
    if (fileSize == INVALID_FILE_SIZE) {
        printf("Error al obtener el tamaño del archivo\n");
        CloseHandle(hFile);
        return;
    }

    // Leer el archivo
    char* buffer = (char*)malloc(fileSize + 1); // +1 = carácter nulo
    if (buffer == NULL) {
        printf("Error de memoria\n");
        CloseHandle(hFile);
        return;
    }

    DWORD bytesRead;
    if (!ReadFile(hFile, buffer, fileSize, &bytesRead, NULL)) {
        printf("Error al leer el archivo\n");
        free(buffer);
        CloseHandle(hFile);
        return;
    }
    buffer[bytesRead] = '\0'; 

    // Mostrar el contenido
    printf("Contenido del archivo:\n%s\n", buffer);

    free(buffer);
    system("pause");
    CloseHandle(hFile);
    menuCopyorView();
}

void Copy() {
    int numArchivos;
    checkIntPosValue("Ingrese la cantidad de archivos a copiar: ", &numArchivos);

    for (int i = 0; i < numArchivos; ++i) {
        char ruta[MAX_PATH];
        char rutacopy[MAX_PATH];

        checkStrValue("Ingrese la ruta del archivo: ", ruta, MAX_PATH);
        HANDLE hSourceFile = CreateFile(ruta, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hSourceFile == INVALID_HANDLE_VALUE) {
            printf("Error al abrir el archivo de origen\n");
            return;
        }

        char sourceFileName[MAX_PATH];
        char destinationPath[MAX_PATH];
        char CopyName[11];
        GetFullPathName(ruta, MAX_PATH, sourceFileName, NULL);


        checkStrValue("Ingrese la ruta para la copia del archivo: ", rutacopy, MAX_PATH - 11);
        GetFullPathName(rutacopy, MAX_PATH - 11, destinationPath, NULL);
        checkStrValue("Ingrese el nombre de la copia (No mas de 10 caracteres incluyendo extension): ", CopyName, 11);
        snprintf(destinationPath, MAX_PATH, "%s\\%s", rutacopy, CopyName);

        HANDLE hDestinationFile = CreateFile(destinationPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hDestinationFile == INVALID_HANDLE_VALUE) {
            printf("Error al crear el archivo de destino\n");
            CloseHandle(hSourceFile);
            return;
        }

        // Leer y escribir datos al archivo copia
        DWORD bytesRead, bytesWritten;
        char buffer[4096];
        while (ReadFile(hSourceFile, buffer, sizeof(buffer), &bytesRead, NULL) && bytesRead > 0) {
            WriteFile(hDestinationFile, buffer, bytesRead, &bytesWritten, NULL);
        }

        CloseHandle(hSourceFile);
        CloseHandle(hDestinationFile);

        printf("Archivo copiado con éxito\n");
    }
    PAUSE;
    menuCopyorView();
}