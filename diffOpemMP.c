#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <omp.h>

const int T = 4;

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

    omp_set_num_threads(T);
#pragma omp parallel private(j) shared(i, matriz)
    {
        unsigned int threadId = omp_get_thread_num();

#pragma omp for
        for (i = 0; i < matriz.linhas; i++)
            for (j = 0; j < matriz.colunas; j++)
                matriz.matriz[i][j] = rand_r(&threadId) % 15;
    }
    return matriz;
}

// double diffQuadratica(mat MAT_A, mat MAT_B)
// {
//     double resultado = 0;
//     int i, j;

//     omp_set_num_threads(T);
// #pragma omp parallel for private(j) shared(i, MAT_A, MAT_B) reduction(+ : resultado)
//     for (i = 0; i < MAT_A.linhas; i++)
//     {
//         for (int j = 0; j < MAT_A.colunas; j++)
//         {
//             double diff = MAT_A.matriz[i][j] * MAT_A.matriz[i][j] - MAT_B.matriz[i][j] * MAT_B.matriz[i][j];
//             resultado += diff;
//         }
//     }

//     return resultado;
// }

double diffQuadratica(mat MAT_A, mat MAT_B)
{
    double resultado = 0;
    int i, j;
    
    int resTMP[MAT_A.linhas];

    omp_set_num_threads(T);
#pragma omp parallel
    {

        #pragma omp for private(j) //shared(i, MAT_A, MAT_B)
        for (i = 0; i   < MAT_A.linhas; i++)
        {
            for (int j = 0; j < MAT_A.colunas; j++)
            {
                MAT_A.matriz[i][j] = (MAT_A.matriz[i][j] * MAT_A.matriz[i][j]) - (MAT_B.matriz[i][j] * MAT_B.matriz[i][j]);
            }
        }

#pragma omp for private(j) // reduce(+,resTMP) shared(i, MAT_A, MAT_B) 
        for (i = 0; i < MAT_A.linhas; i++)
        {
            for (int j = 0; j < MAT_A.colunas; j++)
            {
                resTMP[i] += MAT_A.matriz[i][j];
            }
        }
        
        #pragma omp reduce(+:resultado) for
        for (int i = 0; i < MAT_A.linhas; i++)
        {
            resultado += resTMP[i];
        }
    }

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
    mat mat_a, mat_b;

    mat_a.linhas = atoi(argv[1]);
    mat_a.colunas = atoi(argv[2]);
    mat_b.linhas = atoi(argv[1]);
    mat_b.colunas = atoi(argv[2]);

    mat_a = aloca(mat_a);
    mat_b = aloca(mat_b);

    mat_a = popula(mat_a);
    mat_b = popula(mat_b);

    // print(mat_a);
    // printf("\n");
    // print(mat_b);

    printf("RES : %.2f\n\n", diffQuadratica(mat_a, mat_b));

    return 0;
}
