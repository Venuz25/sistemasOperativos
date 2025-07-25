#include <stdio.h>
#include <windows.h>

#define NUM_PROCESOS 6

void imprimirResultado(HANDLE pipe)
{
    char buffer[1024];
    DWORD bytesRead;
    while (ReadFile(pipe, buffer, sizeof(buffer), &bytesRead, NULL) && bytesRead != 0)
    {
        buffer[bytesRead] = '\0'; // Asegurar que el buffer termine en un null terminator
        printf("%s", buffer);
    }
}

int main()
{
     // Calcular tiempo de ejecución
    double total_time;
    DWORD start, end;
    start = GetTickCount();

    HANDLE pipes[NUM_PROCESOS][2];
    PROCESS_INFORMATION pi[NUM_PROCESOS];
    STARTUPINFO si[NUM_PROCESOS];

    for (int i = 0; i < NUM_PROCESOS; i++)
    {
        SECURITY_ATTRIBUTES sa;
        sa.nLength = sizeof(SECURITY_ATTRIBUTES);
        sa.bInheritHandle = TRUE;
        sa.lpSecurityDescriptor = NULL;

        if (!CreatePipe(&pipes[i][0], &pipes[i][1], &sa, 0))
        {
            printf("Fallo al crear la tuberia para el proceso %d\n", i);
            return 1;
        }

        ZeroMemory(&(si[i]), sizeof(STARTUPINFO));
        si[i].cb = sizeof(STARTUPINFO);
        si[i].hStdOutput = pipes[i][1];
        si[i].hStdError = pipes[i][1];
        si[i].dwFlags |= STARTF_USESTDHANDLES;

        ZeroMemory(&(pi[i]), sizeof(PROCESS_INFORMATION));

        char cmd[50];
        switch (i)
        {
        case 0:
            strcpy(cmd, ".\\suma.exe");
            break;
        case 1:
            strcpy(cmd, ".\\resta.exe");
            break;
        case 2:
            strcpy(cmd, ".\\multiplicacion.exe");
            break;
        case 3:
            strcpy(cmd, ".\\traspuesta.exe");
            break;
        case 4:
            strcpy(cmd, ".\\inversa.exe");
            break;
        case 5:
            strcpy(cmd, ".\\imprimir.exe");
            break;
        default:
            break;
        }

        if (!CreateProcess(NULL, cmd, NULL, NULL, TRUE, 0, NULL, NULL, &(si[i]), &(pi[i])))
        {
            printf("Fallo al invocar CreateProcess para el proceso %d (%d)\n", i, GetLastError());
            return 1;
        }

        CloseHandle(pipes[i][1]);
    }

    end = GetTickCount();
    total_time = (double)(end - start) / 1000.0;
    printf("\n\t----Tiempo de ejecucion fue de: %.6f segundos\n", total_time);

    printf("\n --> RESULTADOS");

    for (int i = 0; i < NUM_PROCESOS; i++)
    {
        WaitForSingleObject(pi[i].hProcess, INFINITE);
        imprimirResultado(pipes[i][0]);
        CloseHandle(pipes[i][0]);
        CloseHandle(pi[i].hProcess);
        CloseHandle(pi[i].hThread);
    }

    return 0;
}
