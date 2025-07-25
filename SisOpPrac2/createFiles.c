
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <stdbool.h>

#include "inputs/inputs.h"
#include "wfile/wfile.h"
#include "main.h"
#include "createFiles.h"

const char text[] = 
"Lorem ipsum dolor sit amet, consectetur adipiscing elit.\n" 
"Nulla rutrum orci et tristique venenatis. Vestibulum ullamcorper feugiat malesuada.\n" 
"Nullam viverra porta pulvinar. Nullam dignissim rhoncus justo ut varius.\n"
"Nam laoreet, magna cursus ullamcorper dictum, tortor nulla ultricies velit, eu varius dui enim eget neque.\n" 
"In sit amet feugiat orci. Nulla mi purus, finibus ac condimentum in, bibendum vitae ligula.\n"
"Aenean vestibulum orci non velit imperdiet pulvinar. Vivamus non quam ut sem cursus gravida.\n" 
"Suspendisse scelerisque rhoncus pulvinar. Praesent mollis vestibulum sodales.\n"
;

int startFunc1()
{
    char path[MAX_PATH], filename[MAX_PATH];
    int archivos = 0;
    bool results;

    HANDLE file;

    checkStrValue("Ingrese la ruta donde desea crear el directorio: ", path, MAX_PATH - 10);
    checkIntPosValue("Ingrese el numero de archivos que desea crear: ", &archivos);

    results = CreateDirectory(path, NULL);

    if (results == false)
	{
		switch (GetLastError())
		{
		case ERROR_PATH_NOT_FOUND:
            printf("Una carpeta intermedia no existe, Escoja otro\n");
            PAUSE;
            return EXIT_FAILURE;
            break;

		case ERROR_ALREADY_EXISTS:
            printf("El directorio ya existe, Escoja otro\n");
            PAUSE;
            return EXIT_FAILURE;
            break;

        default:
            printf("Error desconocido\n");
            PAUSE;
            return EXIT_FAILURE;
            break;
        }
	}

    for (int i = 0; i < archivos; ++i)
	{
        if (i > 0xFFFF)
        {
            sprintf(filename, "%s\\%c%X.txt", path, 'g', i && 0x000F);
        }
        else
        {
            sprintf(filename, "%s\\%04X.txt", path, (short) i);
        }
		
		file = fileCreator(filename, GENERIC_WRITE, 0, CREATE_NEW);

		if (file == INVALID_HANDLE_VALUE)
		{
			printf("Error al crear el archivo %s\n", filename);
			continue;
		}

		if (!windowsFWrite(file, text, strlen(text)))
		{
			printf("Error al escribir en el archivo %s\n", filename);
		}

		CloseHandle(file);
	}

    printf("Terminado\n");
    PAUSE;
    return EXIT_SUCCESS;
}