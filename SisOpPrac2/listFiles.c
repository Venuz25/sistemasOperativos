#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#include <time.h>

#include "inputs/inputs.h"
#include "main.h"
#include "listFiles.h"

void listContents() {
    char directoryPath[MAX_PATH];
    checkStrValue("Ingrese la ruta del directorio a listar: ", directoryPath, MAX_PATH);

    char searchPath[MAX_PATH];
    sprintf(searchPath, "%s\\*", directoryPath);

    WIN32_FIND_DATA findData;
    SYSTEMTIME lastAccessFile;
    HANDLE hFind = FindFirstFile(searchPath, &findData);

    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            if (strcmp(findData.cFileName, ".") != 0 && strcmp(findData.cFileName, "..") != 0) {
                FileTimeToSystemTime(&findData.ftLastAccessTime, &lastAccessFile);
                printf("Nombre: %s\n", findData.cFileName);
                printf("Tamaño: %lld bytes\n", ((long long)findData.nFileSizeHigh << 32) + findData.nFileSizeLow);
                printf("Último acceso (UTC): %hd/%hd/%hd %hd:%hd:%hd.%hd\n", lastAccessFile.wDay, lastAccessFile.wMonth, lastAccessFile.wYear, lastAccessFile.wHour, lastAccessFile.wMinute, lastAccessFile.wSecond, lastAccessFile.wMilliseconds);
                printf("----------------------------------\n");
            }
        } while (FindNextFile(hFind, &findData) != 0);

        FindClose(hFind);
    } else {
        printf("No se encontró el directorio especificado o no se pudo acceder.\n");
    }
    PAUSE;
}
