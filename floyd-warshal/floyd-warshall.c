#include <stdio.h>
#include <limits.h>

#define n 4

void imprimirMatriz(int matriz[][n])
{
    int i, j;
    for (i = 0; i < n; i++)
    {

        for (j = 0; j < n; j++)
        {
            
            if (matriz[i][j] == INT_MAX)
            {
                printf("inf. \t");
            }
            else
            {
                printf("%d \t", matriz[i][j]);
            }
        }
        printf("\n");
    }
}

int min(int a, int b)
{
    return a < b ? a : b;
}

floyd(int grafo[][n])
{
    int dist[n][n], i, j, k;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            dist[i][j] = grafo[i][j];
        }
    }

    for (k = 0; k < n; k++)
    {
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX)
                {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
    imprimirMatriz(dist);
}

int main()
{

    /* FILE *in = fopen("input.in", "r");
    if (!in)
    {
        printf("Erro ao abrir o arquivo!\n");
        exit(-1);
    }

    int n, u, v, p;


    fscanf(in, "%d", &n); //nº de vertices */

    int matriz[n][n] = {{0, 5, INT_MAX, 10},
                        {INT_MAX, 0, 3, INT_MAX},
                        {INT_MAX, INT_MAX, 0, 1},
                        {INT_MAX, INT_MAX, INT_MAX, 0}};
    imprimirMatriz(matriz);

    printf("*********************\n");

    floyd(matriz);
}