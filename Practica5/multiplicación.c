#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int mat1[40][40];
int mat2[40][40];
int multi[40][40];

void guardar()
{
    FILE *ptrs, *ptrs2;
    int i, j;

    ptrs = fopen("matriz1.txt", "r");
    if (ptrs == NULL)
    {
        printf("No se pudo abrir el archivo matriz1.txt");
        exit(1);
    }

    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            if (fscanf(ptrs, "%d", &mat1[i][j]) != 1)
            {
                printf("Error al leer los datos del archivo matriz1.txt");
                exit(1);
            }
        }
    }
    fclose(ptrs);

    ptrs2 = fopen("matriz2.txt", "r");
    if (ptrs2 == NULL)
    {
        printf("No se pudo abrir el archivo matriz2.txt");
        exit(1);
    }

    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            if (fscanf(ptrs2, "%d", &mat2[i][j]) != 1)
            {
                printf("Error al leer los datos del archivo matriz2.txt");
                exit(1);
            }
        }
    }
    fclose(ptrs2);
}

int main()
{
    guardar();
    FILE *fichero;
    fichero = fopen("multi.txt", "w");

    int i, j, k;
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            multi[i][j] = 0;
            for (k = 0; k < 10; k++)
                multi[i][j] += mat1[i][k] * mat2[k][j];
        }
    }

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            fprintf(fichero, "%d ", (int)(multi[i][j]));
        }
        fprintf(fichero, "\n");
    }

    fclose(fichero);
    return 0;
}