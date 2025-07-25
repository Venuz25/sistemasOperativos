#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <windows.h>

#include "main.h"
#include "wfile/wfile.h"
#include "inputs/inputs.h"
#include "createFiles.h"
#include "permissionsFiles.h"
#include "listFiles.h"
#include "copyFiles.h"

#ifndef __MSVCRT__
#error "Only works on Windows environment!!"
#endif

static const char *menuText = 
"Menu de la practica 2:\n"
	"\t1. Crear archivos\n"
	"\t2. Cambiar permisos del archivo\n"
	"\t3. Listar archivos\n"
	"\t4. Copiar archivos\n"
	"\t5. Salir\n"
"opcion: "
;

int main( void )
{
	int opcion = 0;

	SetConsoleCP(UTF8);
	SetConsoleOutputCP(UTF8);
	SetConsoleTitle("Practica 2");

	do
	{
		SCR_CLEAR;
		SetConsoleTitle("Practica 2");
		checkIntPosValue(menuText, &opcion);

		switch (opcion)
		{
		case 1:
			SetConsoleTitle("Practica 2 - Crear carpeta y archivos");
			startFunc1();
			break;
			
		case 2:
			SetConsoleTitle("Practica 2 - Cambiar permisos de archivos");
			cambiarPermisos();
			break;

		case 3:
			SetConsoleTitle("Practica 2 - Listar archivos");
			listContents();
			break;

		case 4:
			SetConsoleTitle("Practica 2 - Copiar/Ver archivos");
			menuCopyorView();
			PAUSE;
			break;
		
		case 5:
			break;

		default:
			printf("Opcion desconocida");
			PAUSE;
			break;
		}
	} while (opcion != 5);
	

	return EXIT_SUCCESS;
}
