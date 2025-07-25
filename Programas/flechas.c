// Imprimir flechas dado un numero
// La mitad de la columna mas grande tambien son el numero de filas - 1
// Resolucion: n x n/2
// Espacios inician desde n/2 - 1

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// For this macros just... make sure that you put ; at the end
#ifdef __MSVCRT__ //Windows
#define SCR_CLEAR system("cls")
#define PAUSE system("pause > null")
#define DELAY system("timeout /T 1")
#elif defined(__APPLE__ && __MACH__) // Ehh... mac?
#define SCR_CLEAR system("clear")
#define PAUSE system("pause")
#define DELAY system("timeout /T 1")
#else // LINUX?
#define SCR_CLEAR system("clear")
#define PAUSE system("read -n 1 -s -p \"Pulsa cualquier tecla para continuar\"")
#define DELAY system("sleep 1")
#endif

#define PRINT_CHAR '*'

/// @brief Verify that the input is an int and also that is a positive number
/// @param msj The messaje to show on screen
/// @param val Where to store the value
void validarDatoEnt(const char *msj, int *val)
{
    SCR_CLEAR;
    printf("%s", msj);
    while ((scanf("%d", val) == 0) && (*val > 0))
    {
        fflush(stdin);
        printf("Ingrese un dato valido!\n");
        PAUSE;
        SCR_CLEAR;
        printf("%s", msj);
    }
}

void printFigure(int num, FILE *output)
{
    int center, centerFig;

    center = ceil(num / 2);
    centerFig = ceil(center / 2);

    for (size_t i = 0; i < (size_t)centerFig; i++) // First part figure
    {
        for (int i2 = 0; i2 < (int)(centerFig - i); i2++) // Triangle
        {
            fprintf(output, " ");
        }
        
        for (size_t j = 0; j < 2 * i + 1; j++)
        {
            fprintf(output, "%c", PRINT_CHAR);
            PAUSE;
        }

        for (int i3 = 0; i3 < (int)(center - i) - 1; i3++) // Line
        {
            fprintf(output, " ");
        }

        for (size_t j = 0; j < 1; j++)
        {
            fprintf(output, "%c", PRINT_CHAR);
            PAUSE;
        }
        fprintf(output, "\n");
    }
    
    for (int i = 0; i < num; i++)
    {
        fprintf(output, "%c", PRINT_CHAR);
        PAUSE;
    }
    fprintf(output, "\n");

    for (size_t i = 0; i < (size_t)centerFig; i++)
    {
        for (int i3 = 0; i3 < centerFig; i3++) // Line
        {
            fprintf(output, " ");
        }
        for (size_t j = 0; j < 1; j++)
        {
            fprintf(output, "%c", PRINT_CHAR);
            PAUSE;
        }

        for (int i2 = 0; i2 < (int)(center - centerFig + i) ; i2++) // Triangle
        {
            fprintf(output, " ");
        }
        
        for (int j = 0; j < (int)(2 * (centerFig - i) - 1); j++)
        {
            fprintf(output, "%c", PRINT_CHAR);
            PAUSE;
        }
        fprintf(output, "\n");
    }
    
}

int main( void )
{
	int num;

	do
	{
		validarDatoEnt("Ingrese un numero par:", &num);
		if((num % 2) != 0)
		{
			SCR_CLEAR;
			printf("Ingrese un numero par, no impar\n");
			PAUSE;
            continue;
		}
        if (((num / 2) % 2) == 0)
        {
            SCR_CLEAR;
            printf("Ingrese otro numero par que dividido entre 2 de uno impar\n");
            printf("Si te es de ayuda para obtener cualquier numero par es solo con la\n");
            printf("operacion: 2 * n (n: es el numero que quieres que resulte ser el centro)\n");
            num = 3;
            PAUSE;
            continue;
        }
        
        if (num < 4)
        {
            num = 3;
            SCR_CLEAR;
            printf("Ingrese un numero mayor a 4\n");
            PAUSE;
            continue;
        }

	}while( (num % 2) != 0 );
	
	printFigure(num, stdout);
    
    int tmp;
    validarDatoEnt("Ingrese 1 para guardar la figura: ", &tmp);
    if (tmp == 1)
    {
        FILE *arch;
        arch = fopen("./figura.txt", "wb");

        if (arch == NULL)
        {
            fprintf(stderr, "No se pudo abrir el archvio\n");
            return EXIT_FAILURE;
        }
        
        printFigure(num, arch);
        fclose(arch);
        printf("Figura guardada con el nombre figura.txt\n");
    }
    
	printf("Listo\n");
	PAUSE;
	return EXIT_SUCCESS;
}