#include <stdio.h>
#include <limits.h>

void imprimirMatriz(int n, int matriz[][n])
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

void floyd(int n, int grafo[][n])
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
    imprimirMatriz(n, dist);
}

int inicializa(int n, int grafo[][n])
{
    int i, j;
    for (i = 0; i < n; i++)
    {

        for (j = 0; j < n; j++)
        {

            grafo[i][j] = INT_MAX;

            if (i == j)
            {
                grafo[i][j] = 0;
            }
        }
    }
}

void lerGrafo(int *in, int n, int grafo[][n])
{

    int u, v, p;

    while (fscanf(in, "%d", &u) != EOF)
    {
        fscanf(in, "%d %d", &v, &p);
        //digrafo
        grafo[u][v] = p;
        grafo[v][u] = p;
    }
}

int main()
{

    FILE *in = fopen("input.in", "r");
    if (!in)
    {
        printf("Erro ao abrir o arquivo!\n");
        exit(-1);
    }

    int n;

    fscanf(in, "%d", &n); //nº de vertices
    int matriz[n][n];

    inicializa(n, matriz);

    lerGrafo(in, n, matriz);
    printf("\n************ Grafo bidirecionado ************\n\n");

    printf("\n *********************\n");

    imprimirMatriz(n, matriz);

    printf("\n *********************\n");

    floyd(n, matriz);
}