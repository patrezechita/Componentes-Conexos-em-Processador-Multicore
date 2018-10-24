#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "comum.h"

typedef struct node {
	int val;
	struct node * next;
} node_t;

typedef struct grafo {
	int val;
	char cor;
	int pai;
	struct node * next;
} grafo_t;

int root = 0;
int *vetorDFS;

void push(grafo_t G[], int val1, int val2);
void DFS_Visita(grafo_t G[], int i);

int main() {
	int **matrizEntrada, qtdVertices, qtdArestas;
	double tempo_total;
	clock_t tempo_inicial, tempo_final;

	// recebe a matriz de entrada da leitura
	matrizEntrada = lerEntrada();

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
	for(int i=0; i<qtdVertices; i++) {	
		G[i].next = NULL;
	}

	// insere as arestas
	for(int i=1; i<qtdArestas; i++) {
		push(G, matrizEntrada[i][0], matrizEntrada[i][1]);
		push(G, matrizEntrada[i][1], matrizEntrada[i][0]);
	}
	
	// DFS
	// para cada vertice, pintar de branco
	for(int i=0; i<qtdVertices; i++) {
		G[i].cor = 'B';
		G[i].pai = -1;
		G[i].val = i;
	}

	// executa o DFS
	for(int i=0; i<qtdVertices; i++) {
		if(G[i].cor == 'B'){
			root = i;
			DFS_Visita(G, i);
		}
	}

	// termina de contar o tempo
	tempo_final = clock();
	tempo_total = (double)(tempo_final - tempo_inicial) / CLOCKS_PER_SEC;
	printf("\n>>> >>> TEMPO GASTO PELO DFS SEQ: %.4lf SEGUNDOS\n\n", tempo_total);

	imprimeSaida("saida_dfs.txt", vetorDFS, qtdVertices);

	return 0;
}

void push(grafo_t G[], int val1, int val2) {
	if(G[val1].next == NULL){
		G[val1].next = malloc(sizeof(node_t));
		G[val1].next->val = val2;
		G[val1].next->next = NULL;
		return;
	}

	node_t * current = G[val1].next;

	// percorre os no da lista ate chegar no ultimo
	while (current->next != NULL) {
		current = current->next;
	}

	//aloca um no
	current->next = malloc(sizeof(node_t));
	current->next->val = val2;
	current->next->next = NULL;
}


void DFS_Visita(grafo_t G[], int i){

	
	G[i].cor = 'C';

	// coloca no vetor quem é o pai
	vetorDFS[i]=root;

	node_t * current = G[i].next;

	while (current != NULL) {


		int u = i;
		int v = current->val;

		if(G[v].cor == 'B'){
			G[v].pai = u;
			DFS_Visita(G, v);
		}

		current = current->next;
	}

	G[i].cor = 'P';
}