#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
#include <limits.h>
#define true 1
#define false 0
typedef int bool;

typedef struct adjacencia
{
    int vert;                //vertice onde a aresta chega
    int peso;                //peso da aresta
    struct adjacencia *prox; //proximo na lista de adj.
} adjacencia;

typedef struct vertice
{
    int item;
    adjacencia *cab;
} vertice;

typedef struct grafo
{
    int n; //numero de vertices
    int m; //numero de arestas
    vertice *adj;

} grafo;

adjacencia *criAdj(int v, int peso)
{
    adjacencia *aux = (adjacencia *)malloc(sizeof(adjacencia));
    aux->vert = v;
    aux->peso = peso;
    aux->prox = NULL;
    return aux;
}

grafo *criaGrafo(int n)
{
    grafo *g = (grafo *)malloc(sizeof(grafo));
    g->n = n;
    g->m = 0;
    g->adj = (vertice *)malloc(n * sizeof(vertice));
    for (int i = 0; i < n; i++)
    {
        g->adj[i].cab = NULL;
    }
    return g;
}

bool criaArestas(grafo *g, int u, int v, int peso)
{
    if (u < 0 || u > g->n)
    {
        return false;
    }
    if (v < 0 || v > g->n)
    {
        return false;
    }

    //adjacencia de v em u
    adjacencia *novo = criAdj(v, peso);
    novo->prox = g->adj[u].cab;
    g->adj[u].cab = novo;

    //adjacencia de u em v
    novo = criAdj(u, peso);
    novo->prox = g->adj[v].cab;
    g->adj[v].cab = novo;

    g->m++;

    return true;
}

bool existeAberto(grafo *g, int *aberto)
{
    for (int i = 0; i < g->n; i++)
    {
        if (aberto[i] == 1)
        {
            return true;
        }
    }
    return false;
}

int menorDist(grafo *g, int aberto[], int dist[])
{
    int i;

    for (i = 0; i < g->n; i++)
    {
        if (aberto[i] == 1)
        {
            break;
        }
    }

    if (i == g->n)
    {
        return -1;
    }

    int menor = i;

    for (i = menor + 1; i < g->n; i++)
    {

        if (aberto[i] == true && dist[i] < dist[menor])
        {
            menor = i;
        }
    }
    //printf("menor=%d\n", menor);
    return menor;
}

int *dijkstra(grafo *g, int s)
{
    int *dist = (int *)malloc(g->n * sizeof(int));
    int prev[g->n];
    bool aberto[g->n];

    for (int v = 0; v < g->n; v++)
    {
        dist[v] = INT_MAX / 2;
        prev[v] = -1;
        aberto[v] = true;
    }

    dist[s] = 0;

    while (existeAberto(g, aberto))
    {
        int u = menorDist(g, aberto, dist);
        aberto[u] = false;

        adjacencia *ad = g->adj[u].cab;

        while (ad != NULL)
        {

            int v = ad->vert;

            while (ad != NULL && ad->vert != v)
            {
                ad = ad->prox;
            }

            if (ad != NULL)
            {
                if (dist[v] > dist[u] + ad->peso)
                {
                    dist[v] = dist[u] + ad->peso;
                    prev[v] = u;
                }
            }

            ad = ad->prox;
        }
    }
    return dist;
}

int main()
{
   
    FILE *in = fopen("input.in", "r");
    if (!in)
    {
        printf("Erro ao abrir o arquivo!\n");
        exit(-1);
    }

    int n, m, s, u, v, p;

    printf("************ \n Observa????o: A numera????o dos v??rtices inic??a-se em 0.\n************\n\n");

    fscanf(in, "%d %d %d", &n, &m, &s);

    printf("numero de v??rtices > %d \n", n);

    printf("numero de arestas > %d \n", m);

    printf("vertice de partida > %d \n", s);

    grafo *g = criaGrafo(n);

    for (int i = 0; i < m; i++)
    {

        fscanf(in, "%d %d %d", &u, &v, &p);

        criaArestas(g, u, v, p);
    }

    //imprimeGrafo(g);

    int *d = dijkstra(g, s);



    printf("\nDistancias:\n\n");

    for (int i = 0; i < g->n; i++)
    {
        printf("(v%d:v%d)  ->  d(%d)\n", s, i, d[i]);
    }
}