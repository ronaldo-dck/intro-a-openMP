#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <omp.h>
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

mat popula(mat matriz)
{
    int i = 0, j = 0;

#pragma omp parallel private(j)
    {
        unsigned int seed = omp_get_thread_num() + clock();
#pragma omp for
        for (i = 0; i < matriz.linhas; i++)
            for (j = 0; j < matriz.colunas; j++)
                matriz.matriz[i][j] = rand_r(&seed) % 11;
    }
    return matriz;
}

void matAoQuadrado(mat *Mat)
{
    int i = 0, j = 0;
#pragma omp parallel for private(j)
    for (i = 0; i < Mat->linhas; i++)
        for (j = 0; j < Mat->colunas; j++)
            Mat->matriz[i][j] *= Mat->matriz[i][j];
}

void matDiff(mat *Mat_A, mat *Mat_B)
{
    int i = 0, j = 0;
#pragma omp parallel for private(j)
    for (i = 0; i < Mat_A->linhas; i++)
        for (j = 0; j < Mat_A->colunas; j++)
            Mat_A->matriz[i][j] -= Mat_B->matriz[i][j];
}

double matSoma(mat *Mat)
{
    double res = 0;
    int i = 0, j = 0;
#pragma omp parallel for private(j) reduction(+:res)
    for (i = 0; i < Mat->linhas; i++)
        for (j = 0; j < Mat->colunas; j++)
            res = res + Mat->matriz[i][j];
    return res;
}

void print(mat matriz)
{
    for (int i = 0; i < matriz.linhas; i++)
    {
        printf("[");
        for (int j = 0; j < matriz.colunas; j++)
            printf("%6.2f ", matriz.matriz[i][j]);
        printf("]\n");
    }
    printf("\n");
}

int main(int argc, char const *argv[4])
{
    double tTotal = 0.0, tInicio, tFinal, tPop = 0.0, tQuad = 0.0, tDiff = 0.0, tSoma = 0.0, inicio, fim;

    tInicio = omp_get_wtime();
    omp_set_num_threads(atoi(argv[3]));

    mat mat_a, mat_b;

    mat_a.linhas = atoi(argv[1]);
    mat_a.colunas = atoi(argv[2]);
    mat_b.linhas = atoi(argv[1]);
    mat_b.colunas = atoi(argv[2]);

    mat_a = aloca(mat_a);
    mat_b = aloca(mat_b);

    inicio = omp_get_wtime();
    mat_a = popula(mat_a);
    mat_b = popula(mat_b);
    fim = omp_get_wtime();
    tPop = fim - inicio;

    // printf("Execucao Paralela\nOriginais:\n");
    // print(mat_a);
    // print(mat_b);

    inicio = omp_get_wtime();
    matAoQuadrado(&mat_a);
    matAoQuadrado(&mat_b);
    fim = omp_get_wtime();
    tQuad = fim - inicio;

    // printf("Quadrados:\n");
    // print(mat_a);
    // print(mat_b);

    inicio = omp_get_wtime();
    matDiff(&mat_a, &mat_b);
    fim = omp_get_wtime();
    tDiff = fim - inicio;

    // printf("Diferenca:\n");
    // print(mat_a);

    double res = 0;
    inicio = omp_get_wtime();
    res = matSoma(&mat_a);
    fim = omp_get_wtime();
    tSoma = fim - inicio;

    tFinal = omp_get_wtime();
    tTotal = tFinal - tInicio;

    FILE *out = fopen("parallel.out", "a");
    fprintf(out, "%s,%f,%f,%f,%f,%f\n", argv[3], tPop, tQuad, tDiff, tSoma, tTotal);
    fclose(out);
    return 0;
}