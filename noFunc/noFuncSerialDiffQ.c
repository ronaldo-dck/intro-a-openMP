#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

typedef struct
{
    unsigned linhas;
    unsigned colunas;
    double **matriz;
} mat;

mat aloca(mat matriz)
{
    matriz.matriz = malloc(matriz.linhas * sizeof(double *));
    for (int i = 0; i < matriz.linhas; i++)
        matriz.matriz[i] = malloc(matriz.colunas * sizeof(double));
    return matriz;
}

void print(mat matriz)
{
    printf("\n[");
    for (int i = 0; i < matriz.linhas; i++)
    {
        printf("[");
        for (int j = 0; j < matriz.colunas; j++)
            printf("%6.2f ", matriz.matriz[i][j]);
        printf("]\n");
    }
    printf("]\n");
}

int main(int argc, char const *argv[3])
{
    float tTotal = 0.0;
    clock_t tInicio, tFinal;

    tInicio = clock();

    mat mat_a, mat_b;

    mat_a.linhas = atoi(argv[1]);
    mat_a.colunas = atoi(argv[2]);
    mat_b.linhas = atoi(argv[1]);
    mat_b.colunas = atoi(argv[2]);

    mat_a = aloca(mat_a);
    mat_b = aloca(mat_b);

    int i = 0, j = 0;
    double res = 0;

    for (i = 0; i < mat_a.linhas; i++)
        for (j = 0; j < mat_a.colunas; j++)
        {
            mat_a.matriz[i][j] = rand() % 11;
            mat_b.matriz[i][j] = rand() % 11;
        }

    for (i = 0; i < mat_a.linhas; i++)
        for (j = 0; j < mat_a.colunas; j++)
        {
            mat_a.matriz[i][j] *= mat_a.matriz[i][j];
            mat_b.matriz[i][j] *= mat_b.matriz[i][j];
        }

    for (i = 0; i < mat_a.linhas; i++)
        for (j = 0; j < mat_a.colunas; j++)
            mat_a.matriz[i][j] -= mat_b.matriz[i][j];

    for (i = 0; i < mat_a.linhas; i++)
        for (j = 0; j < mat_a.colunas; j++)
            res = res + mat_a.matriz[i][j];

    tFinal = clock();
    tTotal = (float)(((tFinal - tInicio) + 0.0) / CLOCKS_PER_SEC);
    printf("Res: %f\ntotal:%f\n", res, tTotal);

    return 0;
}
