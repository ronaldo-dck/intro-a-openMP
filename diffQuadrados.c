#include <stdio.h>
#include <stdlib.h>

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

double diffQuadratica(mat MAT_A, mat MAT_B)
{
    double resultado = 0;

    for (int i = 0; i < MAT_A.linhas; i++)
        for (int j = 0; j < MAT_A.colunas; j++)
            resultado += MAT_A.matriz[i][j] * MAT_A.matriz[i][j] - MAT_B.matriz[i][j] * MAT_B.matriz[i][j];
    return resultado;
}

void print(mat matriz)
{
    printf("\n[");
    for (int i = 0; i < matriz.linhas; i++)
    {
        printf("[");
        for (int j = 0; j < matriz.colunas; j++)
            printf("%.2f ", matriz.matriz[i][j]);
        printf("]\n");
    }
    printf("]\n");
}

int main(int argc, char const *argv[3])
{
    /* TODO
        alocar matrizes
        popular matrizes
        elevar ao quadrado
        diff das matrizes
        somar matriz resultante
     */

    mat mat_a, mat_b, mat_res;

    mat_a.linhas = atoi(argv[1]);
    mat_a.colunas = atoi(argv[2]);
    mat_b.linhas = atoi(argv[1]);
    mat_b.colunas = atoi(argv[2]);

    mat_a = aloca(mat_a);
    mat_b = aloca(mat_b);

    mat_a = popula(mat_a);
    mat_b = popula(mat_b);

    


    double resEscalar = diffQuadratica(mat_a, mat_b);

    printf("RES : %.2f\n\n", resEscalar);


    return 0;
}
