#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "comum.h"

// estrutura da lista de adjacência
typedef struct node {
	int val;
	struct node * next;
} node_t;

// elemento da lista de adjacência
typedef struct grafo {
	//int val; nao ta usando
	char cor;
	int pai;
	struct node * next;
} grafo_t;

// variaveis globais para simplificar as chamadas de funcoes recursivas
int root = 0;
int *vetorDFS;

// declaração de funções
void push(grafo_t G[], int val1, int val2);
void DFS_Visita(grafo_t G[], int i);

int main(int argc, char *argv[]) {
	int **matrizEntrada, qtdVertices, qtdArestas;
	double tempo_total;
	clock_t tempo_inicial, tempo_final;

	// recebe a matriz de entrada da leitura
	matrizEntrada = lerEntrada(argv[1]);

	// comeca a contar o tempo
	tempo_inicial = clock();

	// guarda a quantidade de vertices e arestas
	qtdVertices = matrizEntrada[0][0];
	qtdArestas = matrizEntrada[0][1];

	// aloca espaco para o vetor dos componentes
	vetorDFS = (int *)malloc(qtdVertices * sizeof(int));

	// vetor com todos os grafos
	grafo_t G[qtdVertices];

	// inicializa o grafo
	for(int i=0; i<qtdVertices; i++)
	{	
		G[i].next = NULL;
	}

	// insere as arestas
	for(int i=1; i<qtdArestas; i++)
	{
		push(G, matrizEntrada[i][0], matrizEntrada[i][1]);
		push(G, matrizEntrada[i][1], matrizEntrada[i][0]);
	}
	
	// DFS
	// para cada vertice, pintar de branco
	for(int i=0; i<qtdVertices; i++)
	{
		G[i].cor = 'B';
		G[i].pai = -1;
		//G[i].val = i; nao ta usando
	}

	// executa o DFS
	for(int i=0; i<qtdVertices; i++)
	{
		if(G[i].cor == 'B')
		{
			root = i;
			DFS_Visita(G, i);
		}
	}

	// termina de contar o tempo
	tempo_final = clock();
	tempo_total = (double)(tempo_final - tempo_inicial) / CLOCKS_PER_SEC;
	printf("dfs\t\t%s\t%.4lf\n", argv[1], tempo_total);

	//imprimeSaida("saida_dfs.txt", vetorDFS, qtdVertices);

	return 0;
}

// coloca um no no grafo
void push(grafo_t G[], int val1, int val2)
{
	node_t * current = G[val1].next;
	
	G[val1].next = malloc(sizeof(node_t));
	G[val1].next->val = val2;
	G[val1].next->next = current;
}

// funcao dfs - busca em profundidade
void DFS_Visita(grafo_t G[], int i)
{

	// seta o no na cor cinza - esta sendo visitado
	G[i].cor = 'C';

	// coloca no vetor quem é o pai
	vetorDFS[i]=root;

	node_t * current = G[i].next;

	// percore os nos adjacentes em recursao
	while (current != NULL)
	{

		// variavel auxiliar
		int u = i;
		int v = current->val;

		// se o no e branco, entao visitar ele
		if(G[v].cor == 'B')
		{
			G[v].pai = u;
			
			// chama dfs recursivamente
			DFS_Visita(G, v);
		}

		current = current->next;
	}

	// quando ja visitou todos, setar no com preto
	G[i].cor = 'P';
}