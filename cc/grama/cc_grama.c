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

















int root = 0;

int vetorDFS[999][999];
int tID;
	int thID;
int nThread = 4;
int qtdArestasDFS=0;
int qtdArestaDaTh[4]; //mudar aqui tb para o numero de th
 // nao ta alocado dinamicamente


int find_(int th, int p);
void union_(int th, int qtdVertices, int p, int q);
void push(grafo_t G[], int val1, int val2);
void DFS_Visita(grafo_t G[], int i, int tBegin, int tLast, int** matrizArestas);






















// variáveis globais
int **resultadoDFS;

// declaração de funções
void DFS(grafo_t G[], int i, int vInicial, int vFinal, int vPai, int thID);

// função principal
void main()
{
	int **matrizEntrada, qtdVertices, qtdArestas;

	// recebe a matriz de entrada da leitura
	matrizEntrada = lerEntrada();

	// guarda a quantidade de vértices e arestas
	qtdVertices = matrizEntrada[0][0];
	qtdArestas = matrizEntrada[0][1];

	// cria e inicializa a lista de adjacência
	grafo_t G[qtdVertices];
	for(int i=0; i<qtdVertices; i++)
	{	
		G[i].next = NULL;
	}

	// insere as arestas na lista de adjacência
	for(int i=1; i<qtdArestas; i++)
	{
		push(G, matrizEntrada[i][0], matrizEntrada[i][1]);
		push(G, matrizEntrada[i][1], matrizEntrada[i][0]);
	}
	
	// inicializar os vértices para o DFS
	for(int i=0; i<qtdVertices; i++)
	{
		G[i].cor = 'B';
		G[i].pai = -1;
		G[i].val = i;
	}


	// aloca memória para a matriz de vetores resultadoDFS
	resultadoDFS = malloc(nThread * sizeof(int *));
	for (int i = 0; i < nThread; i++)
	{
		resultadoDFS[i] = malloc(qtdVertices * sizeof(int));
	}

	// vetor que guarda informações auxiliares para as threads
	// quantidade de vértice; vértice inicial; vértice final 
	int infoThread[nThread][3];

	// calcula o piso e o teto para dividir os vértices
	int piso = floor((float)qtdVertices/nThread);
	int teto = ceil((float)qtdVertices/nThread);
	int qtdTeto = qtdVertices - (piso*nThread);
	
	// guarda a quantidade de vértice de cada thread
	for(int i=0; i<nThread; i++)
	{
		if(i < qtdTeto)
			infoThread[i][0] = teto;
		else
			infoThread[i][0] = piso;
	}

	// calcula o vértice inicial e final de cada thread
	int vInicial = 0, vFinal;
	for(int i=0; i<nThread; i++)
	{
		vFinal = vInicial + infoThread[i][0] - 1;
		infoThread[i][1] = vInicial;
		infoThread[i][2] = vFinal;
		vInicial += infoThread[i][0];
	}

	// imprime infoThread para debug
	printf("\ninfoThread\n");
	for(int i=0; i<nThread; i++)
	{
		// thread, quantidade de vértice, vértice inicial e vértice final
		printf("t%d [%d;%d;%d]\n", i, infoThread[i][0], infoThread[i][1], infoThread[i][2]);
	}

	// cada thread inicia o DFS em paralelo
	#pragma omp parallel private(vInicial, vFinal) shared(G, infoThread)
	{
		// identificador único da thread
		int thID = omp_get_thread_num();
		
		// guarda o pai do vértice antes de entrar nele
		int vPai;

		// vértices iniciais e finais
		vInicial = infoThread[thID][1];
		vFinal = infoThread[thID][2];
	
		// limpa o seu vetor resultado do DFS
		for(int i=0; i<qtdVertices; i++)
		{
			resultadoDFS[thID][i] = i;
		}

		// executa o DFS
		for(int i=vInicial; i<=vFinal; i++)
		{
			if(G[i].cor == 'B')
			{
				vPai = i;
				DFS(G, i, vInicial, vFinal, vPai, thID);
			}
		}
	}
	// fim da execução em paralelo

	// imprime vetor dfs para debug
	printf("\nresultadoDFS\n");
	for (int i = 0; i < nThread; i++)
	{
		printf("t%d [", i);
		for (int j = 0; j < qtdVertices; j++)
		{
			printf("%d ", resultadoDFS[i][j]);
		}
			printf("]\n");
	}
































	// criar vetor para cada thr e armazenar a qtd de vertice
	int qtdVetorTh[nThread];
	// calcula o piso e teto

	for(int i=0; i<nThread; i++) {
		qtdVetorTh[i] = piso;
	}
int aux = qtdVertices - (piso*nThread);
	for(int i=0; i<aux; i++) {
		qtdVetorTh[i] = teto;
	}


	
	 //printf("\nInformacoes das threads:\n");


	 int matrizVertThread[nThread][2];

	int tBegin = 0;

	////////////////////////////////////////
	//para cada thread
	for(int i=0; i<nThread; i++) {
		int qtdPorThread = qtdVetorTh[i];
		//int tBegin = i * qtdPorThread; //primeiro elemento da thread
		
		int tLast = tBegin + qtdPorThread - 1; //ultimo elemento da thread
		tID = i;
		
		matrizVertThread[i][0]=tBegin;
		matrizVertThread[i][1]=tLast;
		//printf("t%d tem %d vert. vai do %d ao %d\n", i, qtdPorThread, tBegin, tLast);

	
		// limpa o vetor
		for(int i=0; i<qtdVertices; i++) {
			vetorDFS[tID][i]=i;

		}



		//vetor das arestas
		int **matrizArestas;
		//aloca memoria pro vetor das arestas
		matrizArestas = malloc(qtdArestas * sizeof(int *));
		for (int i = 0; i < qtdArestas; i++) {
			matrizArestas[i] = malloc(2 * sizeof(int));
		}
		//qtd de arestas que vai guardar no dfs
		qtdArestasDFS=0;



		// executa o DFS de cada thread
		for(int i=tBegin; i<=tLast; i++) {
			if(G[i].cor == 'B') {
				root = i;
				//printf("entrei no %d\n", i);
				DFS_Visita(G, i, tBegin, tLast, matrizArestas);
			}
		}
		
		//printf("%d qtd de arestas na mariz\n", qtdArestasDFS);

		for(int i=0; i<qtdArestasDFS; i++) {
		printf("<%d,%d>\n", matrizArestas[i][0], matrizArestas[i][1]);
		}
		qtdArestaDaTh[tID]=qtdArestasDFS;
		printf("\n");


		tBegin += qtdPorThread;
	}

	// printf("\nVetor dfs de cada thread:\n");

	// // imprime vetor dfs para debug
	// for (int i = 0; i < nThread; i++) {
	// 	printf("t%d [", i);
	// 	for (int j = 0; j < qtdVertices; j++) {
	// 		printf("%d ", vetorDFS[i][j]);
	// 	}
	// 		printf("]\n");
	// }

	

// printf("depois das th\n");
// for(int i=0;i<nThread;i++){
// 	printf("th%d tem %d arestas\n", i, qtdArestaDaTh[i]);
// }


//imprime
	// printf("Lista de Adjacencia\n");
	// for(int i=0; i<qtdVertices; i++){
	// 	printf("[%d]", i);
	// 	print_list(G[i].next);
	// 	printf("\n");
	// }

	printf("\n");


	// quantidade de vezes que vai subir a arvore
	int qtdExecucoes = log2(nThread);
	//int auxZ = qtdExecucoes;
	//int nivel = 0;
	int nivel = 1;

	for(int i=qtdExecucoes; i>0; i--){ //exe 3 vezes

		int salto = pow(2,nivel)/2;
		//printf("nivel %d\n", nivel);
		//printf("%f\n", pow(2,i-1));
		int k=0;
		//printf("\n");
		for(int j=0; j<(pow(2, i-1)); j++) { //2^log n vezes
			
			
			//printf("merge de t%d com t%d\n", 2*(j-1)+salto, 2*(j-1)+1+salto);

			k = 2*j*salto;

			//printf("merge arestas de t%d com vetor de t%d\n", k+salto, k);
	




	int ini, fim;
	node_t * iterador;
	ini = matrizVertThread[k+salto][0];
	fim = matrizVertThread[k+salto][1];


	//for das arestas
	for(int i=ini; i<=fim; i++){
		
		int arestaU, arestaV;
		arestaU = i;
		//printf("[%d]", i);
		
		node_t * current = G[i].next;
		
		while (current != NULL) {
			//printf(" -> [%d]", current->val);
			arestaV = current->val;

			///////////////////
			// finalmente faz o merge, amem

			//printf("<%d,%d>\n", arestaU, arestaV);

			union_(k, qtdVertices, arestaU, arestaV);




			//arestaU = arestaV;
			current = current->next;
		}
		
		//printf("\n");


	}

		//imrpime so pra debug
		// 	printf("apos merge, vetor t%d [", k);
		// for (int j = 0; j < qtdVertices; j++) {
		// 	printf("%d ", vetorDFS[k][j]);
		// }
		// 	printf("]\n");

	//atualiza e aumenta a lista de arestas
	matrizVertThread[k][1] = matrizVertThread[k+salto][1];



















		}
		//tBegin += qtdPorThread;

		//nivel++;






nivel++;

	}

	// while(G[0].next != NULL) {
	// 	printf("a\n");

	// }




	  //  node_t * current = head;
    // while (current != NULL) {
    //     printf(" -> [%d]", current->val);
    //     current = current->next;
    // }










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


void DFS_Visita(grafo_t G[], int i, int tBegin, int tLast, int** matrizArestas){

	



	G[i].cor = 'C';

	// coloca no vetor quem é o pai
	vetorDFS[tID][i]=root;

	//printf("colocando %d de pai em %d\n", root, i);

	node_t * current = G[i].next;

	while (current != NULL) {


		int u = i;
		int v = current->val;



		// adiciona a aresta na matriz de arestas
		if(vetorDFS[tID][v]!=root){
			//printf("<%d,%d>\n", u, v);
		
		matrizArestas[qtdArestasDFS][0] = u;
		matrizArestas[qtdArestasDFS][1] = v;
		qtdArestasDFS++;


		}

		//printf("vi o %d\n", v);
		vetorDFS[tID][v]=root;
		//printf("proximo e o %d\n", v);


		if(G[v].cor == 'B'){
			G[v].pai = u;
			
			if(v >= tBegin && v <= tLast) {
				//printf("estou entrando no %d\n", v);
					// coloca de volta a primeira linha


				DFS_Visita(G, v, tBegin, tLast, matrizArestas);
			}
		}

		current = current->next;
	}

	G[i].cor = 'P';
}

int find_(int th, int p) {
	return vetorDFS[th][p];
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
		if(vetorDFS[th][i] == pID || vetorDFS[th][i] == qID) {
			// da o minimo para o pai por motivos de padronizacao
			vetorDFS[th][i] = MINIMO(pID, qID);
		}
	}
}




















void DFS(grafo_t G[], int i, int tBegin, int tLast, int vPai, int thID){

	
	G[i].cor = 'C';

	// coloca no vetor quem é o pai
	resultadoDFS[thID][i]=vPai;

	//printf("colocando %d de pai em %d\n", root, i);

	node_t * current = G[i].next;

	while (current != NULL) {


		int u = i;
		int v = current->val;
		//printf("th%d vi o %d\n", thID,v);
		resultadoDFS[thID][v]=vPai;
		//printf("proximo e o %d\n", v);


		if(G[v].cor == 'B'){
			G[v].pai = u;
	
			if(v >= tBegin && v <= tLast) {
				//printf("estou entrando no %d\n", v);
				
				DFS(G, v, tBegin, tLast, vPai, thID);
			}
		}

		current = current->next;
	}

	G[i].cor = 'P';
}