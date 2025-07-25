#include <windows.h> /* Servidor de la memoria compartida */
#include <stdio.h> /* (ejecutar el servidor antes de ejecutar el cliente)*/
#define TAM_MEM 27 /*Tamaño de la memoria compartida en bytes */
int main(void)
{
 HANDLE hMemCom;
 char *idMemCompartida = "MemoriaCompatida";
 char *apDatos, *apTrabajo, c;
 if((hMemCom =CreateFileMapping(
 INVALID_HANDLE_VALUE, // usa memoria compartida
 NULL, // seguridad por default
 PAGE_READWRITE, // acceso lectura/escritura a la memoria
 0, // tamaño maxixmo parte alta de un DWORD
 TAM_MEM, // tamaño maxixmo parte baja de un DWORD
 idMemCompartida) // identificador de la memoria compartida
 ) == NULL)
 {
 printf("No se creo la memoria compartida: (%i)\n", GetLastError());
 exit(-1);
 }
 if((apDatos=(char *)MapViewOfFile(hMemCom, // Manejador del mapeo
 FILE_MAP_ALL_ACCESS, // Permiso de lectura/escritura en la memoria
 0,
 0,
 TAM_MEM)) == NULL)
 {
 printf("No se enlazo la memoria compartida: (%i)\n", GetLastError());
 CloseHandle(hMemCom);
 exit(-1);
 }
 apTrabajo = apDatos;
 for (c = 'a'; c <= 'z'; c++)
 *apTrabajo++ = c;
 *apTrabajo = '\0';
 while (*apDatos != '*')
 Sleep(1);
 UnmapViewOfFile(apDatos);
 CloseHandle(hMemCom);
 exit(0);
}
