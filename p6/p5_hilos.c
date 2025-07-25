#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

float mat1[40][40] = {{1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {1, 2, 0, 0, 0, 0, 0, 0, 0, 0},
                      {1, 2, 3, 0, 0, 0, 0, 0, 0, 0},
                      {1, 2, 3, 4, 0, 0, 0, 0, 0, 0},
                      {1, 2, 3, 4, 5, 0, 0, 0, 0, 0},
                      {1, 2, 3, 4, 5, 6, 0, 0, 0, 0},
                      {1, 2, 3, 4, 5, 6, 7, 0, 0, 0},
                      {1, 2, 3, 4, 5, 6, 7, 8, 0, 0},
                      {1, 2, 3, 4, 5, 6, 7, 8, 9, 0},
                      {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};

float mat2[40][40] = {{10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
                      {0, 9, 8, 7, 6, 5, 4, 3, 2, 1},
                      {0, 0, 8, 7, 6, 5, 4, 3, 2, 1},
                      {0, 0, 0, 7, 6, 5, 4, 3, 2, 1},
                      {0, 0, 0, 0, 6, 5, 4, 3, 2, 1},
                      {0, 0, 0, 0, 0, 5, 4, 3, 2, 1},
                      {0, 0, 0, 0, 0, 0, 4, 3, 2, 1},
                      {0, 0, 0, 0, 0, 0, 0, 3, 2, 1},
                      {0, 0, 0, 0, 0, 0, 0, 0, 2, 1},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0, 1}};
int mat1t[10][10] = { 0 };
int mat2t[10][10] = { 0 };
float mat1inv[10][10] = { 0 };
float mat2inv[10][10] = { 0 };
int multi[10][10] = { 0 };

char archivo[10000];

void InverseOfMatrix(float matrix[][40], int order, int opc)
{
    float temp;
    for (int i = 0; i < order; i++)
    {
        for (int j = 0; j < 2 * order; j++)
        {
            if (j == (i + order))
                matrix[i][j] = 1;
        }
    }

    for (int i = order - 1; i > 0; i--)
    {
        if (matrix[i - 1][0] < matrix[i][0])
            for (int j = 0; j < 2 * order; j++)
            {
                temp = matrix[i][j];
                matrix[i][j] = matrix[i - 1][j];
                matrix[i - 1][j] = temp;
            }
    }

    for (int i = 0; i < order; i++)
    {
        for (int j = 0; j < 2 * order; j++)
        {
            if (j != i)
            {
                temp = matrix[j][i] / matrix[i][i];
                for (int k = 0; k < 2 * order; k++)
                {
                    matrix[j][k] -= matrix[i][k] * temp;
                }
            }
        }
    }

    for (int i = 0; i < order; i++)
    {
        temp = matrix[i][i];
        for (int j = 0; j < 2 * order; j++)
        {
            matrix[i][j] = matrix[i][j] / temp;
        }
    }

    for (int i = 0; i < order; i++)
    {
        for (int j = order; j < 2 * order; j++)
        {
            if (opc == 0)
                mat1inv[i][j - order] = matrix[i][j];
            else
                mat2inv[i][j - order] = matrix[i][j];
        }
    }
}

void leer(char entrada[])
{
    FILE *ptrs;
    ptrs = fopen(entrada, "r");
    if (ptrs == NULL)
    {
        printf("No hay datos");
        exit(1);
    }
    else
    {
        while (fgets((char *)&archivo, sizeof(archivo), ptrs))
        {
            printf("%s", archivo);
        }
        fclose(ptrs);
    }
}

DWORD WINAPI Suma(LPVOID param) {
    FILE *fichero = fopen("suma.txt", "w");
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            fprintf(fichero, "%d ", (int)(mat1[i][j] + mat2[i][j]));
        }
        fprintf(fichero, "\n");
    }
    fclose(fichero);
    return 0;
}

DWORD WINAPI Resta(LPVOID param) {
    FILE *fichero = fopen("resta.txt", "w");
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            fprintf(fichero, "%d ", (int)(mat1[i][j] - mat2[i][j]));
        }
        fprintf(fichero, "\n");
    }
    fclose(fichero);
    return 0;
}

DWORD WINAPI Multi(LPVOID param) {
    FILE *fichero = fopen("multi.txt", "w");
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

DWORD WINAPI Transpuesta(LPVOID param) {
    FILE *fichero = fopen("traspuesta.txt", "w");
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            mat1t[i][j] = mat1[j][i];
            mat2t[i][j] = mat2[j][i];
        }
    }

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            fprintf(fichero, "%d ", (int)(mat1t[i][j]));
        }
        fprintf(fichero, "\n");
    }
    fprintf(fichero, "\n");
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            fprintf(fichero, "%d ", (int)(mat2t[i][j]));
        }
        fprintf(fichero, "\n");
    }
    fclose(fichero);
    return 0;
}

DWORD WINAPI Inversa(LPVOID param) {
    FILE *fichero = fopen("inversa.txt", "w");
    InverseOfMatrix(mat1, 10, 0);
    InverseOfMatrix(mat2, 10, 1);
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

int main(void)
{
    double total_time;
    clock_t start, end;
    start = clock();

    HANDLE hThreads[5];
    DWORD threadID;

    hThreads[0] = CreateThread(NULL, 0, Suma, NULL, 0, &threadID);
    hThreads[1] = CreateThread(NULL, 0, Resta, NULL, 0, &threadID);
    hThreads[2] = CreateThread(NULL, 0, Multi, NULL, 0, &threadID);
    hThreads[3] = CreateThread(NULL, 0, Transpuesta, NULL, 0, &threadID);
    hThreads[4] = CreateThread(NULL, 0, Inversa, NULL, 0, &threadID);

    WaitForMultipleObjects(5, hThreads, TRUE, INFINITE);

    for (int i = 0; i < 5; i++) {
        CloseHandle(hThreads[i]);
    }

    printf("\n=== Suma ===\n");
    leer("suma.txt");
    printf("\n=== Resta ===\n");
    leer("resta.txt");
    printf("\n=== Multiplicacion ===\n");
    leer("multi.txt");
    printf("\n=== Traspuesta ===\n");
    leer("traspuesta.txt");
    printf("\n=== Inversa ===\n");
    leer("inversa.txt");

    end = clock();
    total_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\n\tTiempo de ejecucion fue de: %f\n", total_time);
    return 0;
}
