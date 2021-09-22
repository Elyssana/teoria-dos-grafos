#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define true 1
#define false 0
typedef int bool;

typedef struct adjacencia
{
    int vert_orig;
    int vert_dest;           //vertice destino
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

/*************************************/
typedef struct HEAP HEAP;
struct HEAP
{
    int size;
    int max_size;
    void **data;
};

typedef struct _node
{
    int priority;
    int index;
    void *data;
} _node;

/*************************************/

void imprimeGrafo(grafo *g)
{
    printf("vertices: %d. Arestas: %d.\n", g->n, g->m);

    for (int i = 0; i < g->n; i++)
    {
        printf("v%d: ", i);
        adjacencia *ad = g->adj[i].cab;
        while (ad)
        {
            printf("v%d(%d) ", ad->vert_dest, ad->peso);
            ad = ad->prox;
        }

        printf("\n");
    }
}

adjacencia *criAdj(int u, int v, int peso)
{
    adjacencia *aux = (adjacencia *)malloc(sizeof(adjacencia));
    aux->vert_orig = u;
    aux->vert_dest = v;
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

    adjacencia *novo = criAdj(u, v, peso);
    novo->prox = g->adj[u].cab;
    g->adj[u].cab = novo;

    g->m++;

    return true;
}

adjacencia *insereNaLista(adjacencia *cabLista, adjacencia *no)
{
    no->prox = cabLista;
    cabLista = no;
    return cabLista; //?? precisa?/
}

/*************************************/
HEAP *create_heap(int size)
{
    HEAP *heap = (HEAP *)malloc(sizeof(HEAP));

    heap->size = 0;
    heap->max_size = size + 1;

    heap->data = (void **)malloc(size * sizeof(void *));
    for (int i = 1; i < size + 1; ++i)
    {
        heap->data[i] = NULL;
    }

    return heap;
}

_node *_create_node(int priority, void *data)
{
    _node *new_node = (_node *)malloc(sizeof(_node));

    new_node->priority = priority;
    new_node->data = data;

    return new_node;
}

int get_parent_index(int i)
{
    return (i / 2);
}

int get_priority(HEAP *h, int index)
{
    return ((_node *)h->data[index])->priority;
}

void swap_index(HEAP *h, int index_1, int index_2)
{
    ((_node *)h->data[index_1])->index = index_2;
    ((_node *)h->data[index_2])->index = index_1;
}

void swap_data(void **item_1, void **item_2)
{
    void *aux = *item_1;
    *item_1 = *item_2;
    *item_2 = aux;
}

void enqueue(HEAP *heap, int priority, void *data)
{
    if (heap->size >= heap->max_size - 1)
    {
        printf("Heap overflow.\n");
    }
    else
    {
        _node *new_node = _create_node(priority, data);

        heap->data[++heap->size] = new_node;
        new_node->index = heap->size;

        int key_index = heap->size;

        int parent_index = get_parent_index(key_index);

        while (parent_index >= 1 && get_priority(heap, key_index) < get_priority(heap, parent_index))
        {

            swap_index(heap, parent_index, key_index);

            swap_data(&heap->data[parent_index], &heap->data[key_index]);

            key_index = parent_index;

            parent_index = get_parent_index(key_index);
        }
    }
}
int get_left_index(int i)
{
    return (2 * i);
}

int get_right_index(int i)
{
    return (2 * i + 1);
}

void min_heapify(HEAP *heap, int i)
{
    int smallest;
    int left_index = get_left_index(i);
    int right_index = get_right_index(i);

    _node *t = heap->data[i];
    _node *t_l = heap->data[left_index];
    _node *t_r = heap->data[right_index];

    if (left_index <= heap->size && t_l->priority < t->priority)
    {
        smallest = left_index;
    }
    else
    {
        smallest = i;
    }

    _node *t_s = heap->data[smallest];

    if (right_index <= heap->size && t_r->priority < t_s->priority)
    {
        smallest = right_index;
        t_s = heap->data[smallest];
    }

    if (t != t_s)
    {
        swap_index(heap, i, smallest);
        swap_data(&heap->data[i], &heap->data[smallest]);
        min_heapify(heap, smallest);
    }
}

void *dequeue(HEAP *heap)
{
    if (!(heap->size))
    {
        printf("Heap underflow.\n");
        return NULL;
    }
    else
    {
        _node *item = (_node *)heap->data[1];

        heap->data[1] = heap->data[heap->size];

        heap->data[heap->size] = NULL;

        heap->size -= 1;

        min_heapify(heap, 1);

        return item->data;
    }
}

void heap_insert(HEAP *heap, grafo *graph)
{
    for (int i = 0; i < graph->n; i++)
    {
        adjacencia *current = graph->adj[i].cab;
        while (current != NULL)
        {
            enqueue(heap, current->peso, current);
            current = current->prox;
        }
    }
}

/*************************************/

int find(int *pai, int x)
{
    if (pai[x] != x)
    {
        pai[x] = find(pai, pai[x]);
    }
    return pai[x];
}

void Union(int *pai, int *rank, int x, int y)
{
    if (rank[x] >= rank[y])
    {
        pai[y] = x;
        if (rank[x] == rank[y])
        {
            rank[x]++;
        }
    }
    else
    {
        pai[x] = y;
    }
}

void imprimeLista(adjacencia *lista)
{
    int pesoTotal = 0;
    while (lista != NULL)
    {
        printf("(%d,%d) ", lista->vert_orig, lista->vert_dest);

        pesoTotal += lista->peso;
        lista = lista->prox;
    }
    //printf("Peso Total: %d\n", total_weight);
}

void kruskal(grafo *g)
{

    int pai[g->n], rank[g->n];

    adjacencia *T = NULL;

    for (int i = 0; i < g->n; i++)
    {
        pai[i] = i;
        rank[i] = 0;
    }
    HEAP *heap = create_heap(g->m);
    heap_insert(heap, g);

    while (heap->size != 0)
    {
        adjacencia *atual = (adjacencia *)dequeue(heap);

        if (find(pai, atual->vert_orig) != find(pai, atual->vert_dest))
        {
            T = insereNaLista(T, atual);
            Union(pai, rank, find(pai, atual->vert_orig), find(pai, atual->vert_dest));
        }
    }

    imprimeLista(T);
}

int main()
{
    /* 
    grafo *g = criaGrafo(6);

    criaArestas(g, 0, 1, 5);
    criaArestas(g, 0, 2, 4);
    criaArestas(g, 0, 3, 2);
    criaArestas(g, 0, 5, 6);
    criaArestas(g, 1, 3, 1);
    criaArestas(g, 1, 4, 7);
    criaArestas(g, 2, 4, 6);
    criaArestas(g, 3, 5, 1); */


    FILE *in = fopen("input.in", "r");
    if (!in)
    {
        printf("Erro ao abrir o arquivo.\n");
        exit(-1);
    }

    int n, u, v, p;

    printf("************ \n Observação: A numeração dos vértices inicía-se em 0.\n************\n\n");

    fscanf(in, "%d", &n); //nº de vertices

    grafo *g = criaGrafo(n);

    while (fscanf(in, "%d", &u) != EOF)
    {
        fscanf(in, "%d %d", &v, &p);
        criaArestas(g, u, v, p);
    }

    //imprimeGrafo(g);

    kruskal(g);
}