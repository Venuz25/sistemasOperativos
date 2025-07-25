#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

#include "main.h"
#include "permissionsFiles.h"
#include "./inputs/inputs.h"

static const char *menuText = 
"Menu de permisos:\n"
	"\t1. Solo lectura\n"
	"\t2. Escritura\n"
	"\t3. Lectura y escritura\n"
	"\t4. Salir\n"
"opcion: "
;

void cambiarPermisos() {
	char ruta[MAX_PATH];
	int opcion;
	
	checkStrValue("Ingrese la ruta del archivo: ", ruta, MAX_PATH);
	DWORD attr = GetFileAttributes(ruta);
    if (attr == INVALID_FILE_ATTRIBUTES) {
        printf("No se pudo acceder al archivo.\n");
        return;
    }
    
    checkIntPosValue(menuText, &opcion);
    switch (opcion) {
        case 1:
            attr |= FILE_ATTRIBUTE_READONLY;
            break;
        case 2:
            attr &= ~FILE_ATTRIBUTE_READONLY;
            break;
        case 3:
            attr &= ~FILE_ATTRIBUTE_READONLY;
            break;
		case 4: break;
        default:
            printf("Opción inválida.\n");
            return;
    }

    if (!SetFileAttributes(ruta, attr)) {
        printf("Error al cambiar los permisos del archivo.\n");
        return;
    }

    printf("Permisos cambiados exitosamente.\n");
}