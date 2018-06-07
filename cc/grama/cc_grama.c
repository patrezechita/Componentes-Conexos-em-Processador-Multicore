#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include "comum.h"

// retorna o mínimo entre dois valores
#define MINIMO(x,y) (((x)<(y))?(x):(y))

// estrutura da lista de adjacência
typedef struct node
{
	int val;
	struct node * next;
} node_t;

// elemento da lista de adjacência
typedef struct grafo
{
	int val;
	char cor;
	int pai;
	struct node * next;
} grafo_t;

// declaração de funções
void DFS(grafo_t G[], int i, int vInicial, int vFinal, int vPai, int thID);
void push(grafo_t G[], int val1, int val2);
void union_(int th, int qtdVertices, int p, int q);
int find_(int th, int p);

// variáveis globais
int structAresta[999][999][2]; // falta alocar dinamicamente
int **resultadoDFS;
int *qtdStructAresta;

// função principal
int main()
{
	// declaração de variáveis
	int **matrizEntrada;
	int qtdVertices, qtdArestas, thID, piso, teto, qtdTeto;
	int i, j, k, vPai, vFinal, vInicial=0;
	int qtdExecucoes, salto, nivel=1;
	
	// define a quantidade de threads disponível
	int nThread = omp_get_max_threads();

	// vetor que guarda informações auxiliares para as threads
	// quantidade de vértice; vértice inicial; vértice final 
	int infoThread[nThread][3];

	// recebe a matriz de entrada da leitura
	matrizEntrada = lerEntrada();

	// guarda a quantidade de vértices e arestas
	qtdVertices = matrizEntrada[0][0];
	qtdArestas = matrizEntrada[0][1];

	// cria e inicializa a lista de adjacência
	grafo_t G[qtdVertices];
	for(i=0; i<qtdVertices; i++)
	{	
		G[i].next = NULL;
	}

	// insere as arestas na lista de adjacência
	for(i=1; i<qtdArestas; i++)
	{
		push(G, matrizEntrada[i][0], matrizEntrada[i][1]);
		push(G, matrizEntrada[i][1], matrizEntrada[i][0]);
	}
	
	// inicializar os vértices para o DFS
	for(i=0; i<qtdVertices; i++)
	{
		G[i].cor = 'B';
		G[i].pai = -1;
		G[i].val = i;
	}

	// aloca memória para a matriz de vetores resultadoDFS
	resultadoDFS = malloc(nThread * sizeof(int *));
	for (i = 0; i < nThread; i++)
	{
		resultadoDFS[i] = malloc(qtdVertices * sizeof(int));
	}

	// aloca memória para o vetor qtdStructArestas
	qtdStructAresta = malloc(nThread * sizeof(int *));

	// calcula o piso e o teto para dividir os vértices
	piso = floor((float)qtdVertices/nThread);
	teto = ceil((float)qtdVertices/nThread);
	qtdTeto = qtdVertices - (piso*nThread);
	
	// guarda a quantidade de vértice de cada thread
	for(i=0; i<nThread; i++)
	{
		if(i < qtdTeto)
			infoThread[i][0] = teto;
		else
			infoThread[i][0] = piso;
	}

	// guarda os vértices inicial e final de cada thread
	for(i=0; i<nThread; i++)
	{
		vFinal = vInicial + infoThread[i][0] - 1;
		infoThread[i][1] = vInicial;
		infoThread[i][2] = vFinal;
		vInicial += infoThread[i][0];
	}

	// cada thread inicia o DFS em paralelo
	#pragma omp parallel for private(thID, vPai, i, vInicial, vFinal) shared(G, infoThread)
	for(thID=0; thID<nThread; thID++)
	{
		// vértices iniciais e finais
		vInicial = infoThread[thID][1];
		vFinal = infoThread[thID][2];
	
		// limpa o seu vetor resultado do DFS
		for(i=0; i<qtdVertices; i++)
		{
			resultadoDFS[thID][i] = i;
		}

		// limpa qtdStructAresta
		qtdStructAresta[thID] = 0;

		// executa o DFS
		for(i=vInicial; i<=vFinal; i++)
		{
			if(G[i].cor == 'B')
			{
				vPai = i;
				DFS(G, i, vInicial, vFinal, vPai, thID);
			}
		}
	}
	// fim da execução em paralelo

	// imprime infoThread para debug
	printf("\ninfoThread\n");
	for(i=0; i<nThread; i++)
	{
		// thread, quantidade de vértice, vértice inicial e vértice final
		printf("t%d [%d;%d;%d]\n", i, infoThread[i][0], infoThread[i][1], infoThread[i][2]);
	}

	// imprime vetor dfs para debug
	printf("\nresultadoDFS\n");
	for (i = 0; i < nThread; i++)
	{
		printf("t%d [", i);
		for (j = 0; j < qtdVertices; j++)
		{
			printf("%d ", resultadoDFS[i][j]);
		}
			printf("]\n");
	}

	// imprime structAresta para debug
	printf("\nstructAresta\n");
	for (i = 0; i < nThread; i++)
	{
		printf("t%d: ", i);
		for (j = 0; j < qtdStructAresta[i]; j++)
		{
			printf("[%d;%d] ", structAresta[i][j][0], structAresta[i][j][1]);
		}
		printf("\n");
	}

	// calcula a quantidade de níveis da árvore de execução
	qtdExecucoes = log2(nThread);

	// para cada nível da árvore
	printf("\nordem dos union-find\n");
	for(i=qtdExecucoes; i>0; i--)
	{
		k=0;
		salto = pow(2,nivel)/2;

		// execução de um par de threads (union-find)
		for(j=0; j < (pow(2,i-1)); j++)
		{
			k = 2*j*salto;
			printf("union-find de t%d com t%d\n", k, k+salto);
		}

		nivel++;
	}

	// TEM QUE DESALOCAR AS COISAS
	// FAZER ISSO AQUI
	return 0;
}


// função de busca em profundidade
void DFS(grafo_t G[], int i, int tBegin, int tLast, int vPai, int thID)
{
	int u, v;

	// marca o vértice com a cor cinza
	G[i].cor = 'C';

	// coloca no vetor DFS o pai do atual vértice
	resultadoDFS[thID][i]=vPai;

	// auxiliar para ver o próximo vértice
	node_t * current = G[i].next;

	// ver todos os vértices da lista de adjacência
	while (current != NULL)
	{
		// vértices da aresta
		u = i;
		v = current->val;

		// se for aresta da DFS, adiciona a aresta na matriz de arestas
		if(resultadoDFS[thID][v]!=vPai)
		{
			structAresta[thID][qtdStructAresta[thID]][0] = u;
			structAresta[thID][qtdStructAresta[thID]][1] = v;
			qtdStructAresta[thID]++;
		}

		// atualiza o pai do vértice
		resultadoDFS[thID][v]=vPai;

		// se o vértice está no seu "range" olha
		// se não, ignora
		if(v >= tBegin && v <= tLast)
		{
			// se o vértice é branco, então não foi visitado
			if(G[v].cor == 'B')
			{
				// atualiza o pai e chama o DFS
				G[v].pai = u;
				DFS(G, v, tBegin, tLast, vPai, thID);
			}
		}

		// próximo vértice
		current = current->next;
	}

	// percorreu todo o caminho do vértice, marcar de preto
	G[i].cor = 'P';
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




int find_(int th, int p) {
	return resultadoDFS[th][p];
}

void union_(int th, int qtdVertices, int p, int q) {
	int pID = find_(th, p);
	int qID = find_(th, q);

	// se os pais sao iguais, ja estao no mesmo componente
	if(pID == qID)
		return;

	// faz union de dois vertices
	// percorre o vetor para atualiar todos os pais
	for(int i=0; i<qtdVertices; i++) {
		if(resultadoDFS[th][i] == pID || resultadoDFS[th][i] == qID) {
			// da o minimo para o pai por motivos de padronizacao
			resultadoDFS[th][i] = MINIMO(pID, qID);
		}
	}
}
