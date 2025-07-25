#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

int main()
{
    double total_time;
    clock_t start, end;
    start = clock();

    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&(si), sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&(pi), sizeof(pi));

    if (!CreateProcess(NULL, ".\\suma.exe", NULL, NULL, FALSE, 0, NULL, NULL, &(si), &(pi)))
    {
        printf("Fallo al invocar CreateProcess (%d)\n", GetLastError());
        return 1;
    }
    if (!CreateProcess(NULL, ".\\resta.exe", NULL, NULL, FALSE, 0, NULL, NULL, &(si), &(pi)))
    {
        printf("Fallo al invocar CreateProcess (%d)\n", GetLastError());
        return 1;
    }
    if (!CreateProcess(NULL, ".\\multiplicacion.exe", NULL, NULL, FALSE, 0, NULL, NULL, &(si), &(pi)))
    {
        printf("Fallo al invocar CreateProcess (%d)\n", GetLastError());
        return 1;
    }

    if (!CreateProcess(NULL, ".\\traspuesta.exe", NULL, NULL, FALSE, 0, NULL, NULL, &(si), &(pi)))
    {
        printf("Fallo al invocar CreateProcess (%d)\n", GetLastError());
        return 1;
    }
    if (!CreateProcess(NULL, ".\\inversa.exe", NULL, NULL, FALSE, 0, NULL, NULL, &(si), &(pi)))
    {
        printf("Fallo al invocar CreateProcess (%d)\n", GetLastError());
        return 1;
    }
    if (!CreateProcess(NULL, ".\\imprimir.exe", NULL, NULL, FALSE, 0, NULL, NULL, &(si), &(pi)))
    {
        printf("Fallo al invocar CreateProcess (%d)\n", GetLastError());
        return 1;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    end = clock();
    total_time = ((double)(end - start)) / CLK_TCK;

    printf("\n\t----Tiempo de ejecucion fue de: %f\n", total_time);
    return 0;
}