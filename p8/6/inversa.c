#include <stdio.h>
#include <string.h>
#include <stdlib.h>

float mat1[40][40];
float mat2[40][40];
float mat1inv[40][40];
float mat2inv[40][40];

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
            if (fscanf(ptrs, "%f", &mat1[i][j]) != 1)
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
            if (fscanf(ptrs2, "%f", &mat2[i][j]) != 1)
            {
                printf("Error al leer los datos del archivo matriz2.txt");
                exit(1);
            }
        }
    }
    fclose(ptrs2);
}

void InverseOfMatrix(float matrix[][40], int order, int opc)
{
    float temp;
    float augmented[40][80];

    for (int i = 0; i < order; i++)
    {
        for (int j = 0; j < 2 * order; j++)
        {
            if (j < order)
            {
                augmented[i][j] = matrix[i][j];
            }
            else
            {
                augmented[i][j] = (i == (j - order)) ? 1 : 0;
            }
        }
    }

    for (int i = 0; i < order; i++)
    {
        temp = augmented[i][i];
        for (int j = 0; j < 2 * order; j++)
        {
            augmented[i][j] /= temp;
        }

        for (int k = 0; k < order; k++)
        {
            if (k != i)
            {
                temp = augmented[k][i];
                for (int j = 0; j < 2 * order; j++)
                {
                    augmented[k][j] -= temp * augmented[i][j];
                }
            }
        }
    }

    for (int i = 0; i < order; i++)
    {
        for (int j = 0; j < order; j++)
        {
            if (opc == 0)
                mat1inv[i][j] = augmented[i][j + order];
            else
                mat2inv[i][j] = augmented[i][j + order];
        }
    }
}

int main()
{
    guardar();
    InverseOfMatrix(mat1, 10, 0);
    InverseOfMatrix(mat2, 10, 1);
    FILE *fichero;
    fichero = fopen("inversa.txt", "w");
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            fprintf(fichero, "%.3f ", (float)(mat1inv[i][j]));
        }
        fprintf(fichero, "\n");
    }
    fprintf(fichero, "\n");
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            fprintf(fichero, "%.3f ", (float)(mat2inv[i][j]));
        }
        fprintf(fichero, "\n");
    }
    fclose(fichero);
    return 0;
}