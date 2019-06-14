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
	//int val; não tá usando
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
int ***structAresta;
int **resultadoDFS;
int *qtdStructAresta;
int *n_arestas;

// função principal
int main(int argc, char *argv[])
{
	// declaração de variáveis
	int **matrizEntrada;
	int qtdVertices, qtdArestas, thID, piso, teto, qtdTeto;
	int i, vPai, vFinal, vInicial=0;
	int qtdExecucoes, qtdUnions;
	int tEsq, tDir, p, u, v;
	int t, a;
	double tempo_inicial, tempo_final;
	
	// define a quantidade de threads disponível
	int nThread = omp_get_max_threads();

	// cso seja informada, fixar a quantidade de threads
	if(argv[2] != NULL)
	{
		nThread = atol(argv[2]);
	}

	// é necessário que o número de threads seja potência de 2
	if(ceil(log2(nThread)) != floor(log2(nThread)))
	{
		printf("O número de threads [%d] não é potência de 2!\n", nThread);
		return 0;
	}

	// vetor que guarda informações auxiliares para as threads
	// quantidade de vértice; vértice inicial; vértice final 
	int infoThread[nThread][3];

	// recebe a matriz de entrada da leitura
	matrizEntrada = lerEntrada(argv[1]);

	// comeca a contar o tempo
	tempo_inicial = omp_get_wtime();
	
	// guarda a quantidade de vértices e arestas
	qtdVertices = matrizEntrada[0][0];
	qtdArestas = matrizEntrada[0][1];

	// aloca memoria para a estrutura principal
	n_arestas = malloc (nThread * sizeof(int)) ;
	structAresta = malloc (nThread * sizeof(int **)) ;
	for (t = 0 ; t < nThread ; t ++)
	{
		n_arestas[t] = 0 ;

		structAresta[t] = malloc ((qtdVertices - 1) * sizeof(int *)) ;

		for (a = 0 ; a < qtdVertices - 1 ; a ++)
		{
			structAresta[t][a] = malloc (2 * sizeof(int)) ;
		}
	}

	// aloca memória para a matriz de vetores resultadoDFS
	resultadoDFS = malloc(nThread * sizeof(int *));
	for (i = 0; i < nThread; i++)
	{
		resultadoDFS[i] = malloc(qtdVertices * sizeof(int));
	}

	// aloca memória para o vetor qtdStructArestas
	qtdStructAresta = malloc(nThread * sizeof(int *));

	// cria e inicializa a lista de adjacência
	grafo_t G[qtdVertices];
	for(i=0; i<qtdVertices; i++)
	{	
		G[i].next = NULL;
	}

	// inicializar os vértices para o DFS
	for(i=0; i<qtdVertices; i++)
	{
		G[i].cor = 'B';
		G[i].pai = -1;
		//G[i].val = i; não ta usando
	}

	// // comeca a contar o tempo sem alocacao e sem inicializacao
	// tempo_inicial_sem_aloc = omp_get_wtime();

	// insere as arestas na lista de adjacência
	for(i=1; i<qtdArestas; i++)
	{
		push(G, matrizEntrada[i][0], matrizEntrada[i][1]);
		push(G, matrizEntrada[i][1], matrizEntrada[i][0]);
	}

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

	// calcula a quantidade de níveis da árvore de execução
	qtdExecucoes = log2(nThread);

	// calcula quantos UF irá fazer no nivel 0
	qtdUnions = nThread/2;

	// para cada nível da árvore
	// printf("\nordem dos union-find\n");
	for(i=0; i<qtdExecucoes; i++)
	{
		// executa em paralelo um nível da árvore
		#pragma omp parallel for private(thID, tEsq, tDir, u, v, p)
		for(thID=0; thID<qtdUnions; thID++)
		{
			// calcula os índices de onde será acessado
			tEsq = thID * pow(2, (i+1));
			tDir = tEsq + pow(2, i);

			// imprime qual merge está acontecendo, para debug
			// printf("core%d faz UF de t%d com t%d; nivel %d\n", thID, tEsq, tDir, i);
		
			// para cada aresta na thread da direita
			// faz union no vetor da thread da esquerda
			for(p=0; p<qtdStructAresta[tDir]; p++)
			{
				u = structAresta[tDir][p][0];
				v = structAresta[tDir][p][1];
				union_(tEsq, qtdVertices, u, v);
			}
		}
		// divide em dois a quantidade de UF para criar somente
		// a quantidade de threads que precisa (1 por UF)
		qtdUnions = qtdUnions/2;
	}

	// // termina de contar o tempo sem alocacao e sem inicializacao
	// tempo_final_sem_aloc = omp_get_wtime() - tempo_inicial_sem_aloc;

	// desalocação de memória
	free(n_arestas);
	for (t = 0 ; t < nThread ; t ++)
	{
		for (a = 0 ; a < qtdVertices - 1 ; a ++)
		{
			free(structAresta[t][a]) ;
		}
		free(structAresta[t]) ;
	}

	free(structAresta) ;

	// termina de contar o tempo
	tempo_final = omp_get_wtime() - tempo_inicial;
	printf("grama %dth \t%s\t%.4lf\n", nThread, argv[1], tempo_final);
	// printf("gramaSEM\t%s\t%.4lf\n", argv[1], tempo_final_sem_aloc);

	// usa essa funcao pra imprimir a saida e verificar o resultado do algoritmo
	//imprimeSaida("saida_grama.txt", resultadoDFS[0], qtdVertices);

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

// funcao que insere um no no grafo
void push(grafo_t G[], int val1, int val2) 
{
	node_t * current = G[val1].next;
	
	G[val1].next = malloc(sizeof(node_t));
	G[val1].next->val = val2;
	G[val1].next->next = current;
}

// retorna o pai do no
int find_(int th, int p)
{
	return resultadoDFS[th][p];
}

// faz union entre dois vertices
void union_(int th, int qtdVertices, int p, int q)
{
	int pID = find_(th, p);
	int qID = find_(th, q);
	int aux;

	// se os pais sao iguais, ja estao no mesmo componente
	if(pID == qID)
		return;

	// faz union de dois vertices
	// percorre o vetor para atualiar todos os pais
	for(int i=0; i<qtdVertices; i++)
	{
		if(resultadoDFS[th][i] == pID || resultadoDFS[th][i] == qID)
		{
			// da o minimo para o pai por motivos de padronizacao
			resultadoDFS[th][i] = MINIMO(pID, qID);
		}
	}

	// atualiza  alista de arestas
	aux = qtdStructAresta[th];
	structAresta[th][aux][0] = p;
	structAresta[th][aux][1] = q;
	qtdStructAresta[th]++;
	return;
}