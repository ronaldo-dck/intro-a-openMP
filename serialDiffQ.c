#include <stdio.h>
#include <stdlib.h>
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
    for (int i = 0; i < matriz.linhas; i++)
        for (int j = 0; j < matriz.colunas; j++)
            matriz.matriz[i][j] = rand() % 11;
    return matriz;
}

void matAoQuadrado(mat *Mat)
{
    for (int i = 0; i < Mat->linhas; i++)
        for (int j = 0; j < Mat->colunas; j++)
            Mat->matriz[i][j] *= Mat->matriz[i][j];
}

void matDiff(mat *Mat_A, mat *Mat_B)
{
    for (int i = 0; i < Mat_A->linhas; i++)
        for (int j = 0; j < Mat_A->colunas; j++)
            Mat_A->matriz[i][j] -= Mat_B->matriz[i][j];
}

double matSoma(mat *Mat)
{
    double res = 0;
    for (int i = 0; i < Mat->linhas; i++)
        for (int j = 0; j < Mat->colunas; j++)
            res += Mat->matriz[i][j];
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

int main(int argc, char const *argv[3])
{
    float tTotal = 0.0, tPop = 0.0, tQuad = 0.0, tDiff = 0.0, tSoma = 0.0;
    clock_t tInicio, tFinal, inicio, fim;
    tInicio = clock();
    mat mat_a, mat_b;

    mat_a.linhas = atoi(argv[1]);
    mat_a.colunas = atoi(argv[2]);
    mat_b.linhas = atoi(argv[1]);
    mat_b.colunas = atoi(argv[2]);

    mat_a = aloca(mat_a);
    mat_b = aloca(mat_b);

    srand(clock());
    inicio = clock();
    mat_a = popula(mat_a);
    mat_b = popula(mat_b);
    fim = clock();
    tPop = (float)(((fim - inicio) + 0.0) / CLOCKS_PER_SEC);

    // printf("Execucao Serial\nOriginais:\n");
    // print(mat_a);
    // print(mat_b);

    inicio = clock();
    matAoQuadrado(&mat_a);
    matAoQuadrado(&mat_b);
    fim = clock();
    tQuad = (float)(((fim - inicio) + 0.0) / CLOCKS_PER_SEC);

    // printf("Quadrados:\n");
    // print(mat_a);
    // print(mat_b);

    inicio = clock();
    matDiff(&mat_a, &mat_b);
    fim = clock();
    tDiff = (float)(((fim - inicio) + 0.0) / CLOCKS_PER_SEC);

    // printf("Diferenca:\n");
    // print(mat_a);

    double res = 0;
    inicio = clock();
    res = matSoma(&mat_a);
    fim = clock();
    tSoma = (float)(((fim - inicio) + 0.0) / CLOCKS_PER_SEC);

    tFinal = clock();
    tTotal = (float)(((tFinal - tInicio) + 0.0) / CLOCKS_PER_SEC);

    FILE *out = fopen("serial.out", "a");
    fprintf(out, "%f,%f,%f,%f,%f\n", tPop, tQuad, tDiff, tSoma, tTotal);
    fclose(out);
    return 0;
}