#include <windows.h> /*Programa hijo*/
#include <stdio.h>
int main()
{
    HANDLE hSemaforo;
    int i=1;

    // Apertura del semáforo
    if((hSemaforo = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "Semaforo")) == NULL) {
        printf("Falla al invocar OpenSemaphore: %d\n", GetLastError());
        return -1;
    }

    while(i<4) {
        // Prueba del semáforo
        WaitForSingleObject(hSemaforo, INFINITE);

        //Sección crítica
        printf("Soy el hijo entrando %i de 3 veces al semaforo\n",i);
        Sleep(5000);

        //Liberación el semáforo
        if (!ReleaseSemaphore(hSemaforo, 1, NULL) ) {
            printf("Falla al invocar ReleaseSemaphore: %d\n", GetLastError());
        }
        printf("Soy el hijo liberando %i de 3 veces al semaforo\n",i);
        Sleep(5000);

        i++;
    }
}
