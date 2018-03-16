#include <stdio.h>
#include <stdlib.h>
#include <limits.h>




typedef struct node {
    int val;
    struct node * next;
} node_t;


typedef struct grafo {
    int val;
    int d;
	int f;
	char cor;
	int pai;
    struct node * next;
} grafo_t;

	//variavel global tempo
	int tempo = 0;
	int iteradorF = 0;
		int vetorF[999];
	int imprimeSCC = 0;

void print_list(node_t * head) {
    node_t * current = head;

    while (current != NULL) {
        printf(" -> [%d]", current->val);
        current = current->next;
    }
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

	tempo = tempo +1;
	G[i].d = tempo;
	G[i].cor = 'C';

if(imprimeSCC==1)
	printf("%d ", i);

	node_t * current = G[i].next;

    while (current != NULL) {

    	//printf("G[%d] ", i);
        //printf(" [%d] ", current->val);
        int u = i;
        int v = current->val;

        if(G[v].cor == 'B'){
        	G[v].pai = u;
        	DFS_Visita(G, v);
        }

        current = current->next;
    }

    G[i].cor = 'P';
    tempo = tempo+1;
    vetorF[iteradorF]=i;
    iteradorF++;
    G[i].f = tempo;

    //if(G[i].pai == -1)
    //	G[i].pai = i;

}

void main() {
//	printf("ola\n");


	// le o arquivo de entrada
	FILE *arqEntrada;
	arqEntrada = fopen("grafo.txt", "r");


		// se nao achar o arquivo, reportar e sair
	if (arqEntrada == NULL) {
		printf("Arquivo nao encontrado.\n");
		exit(0);
	}


	int qtdGrafos, qtdArestas;

	// guarda o tamanho da matriz quadrada
	fscanf(arqEntrada, "%d %d", &qtdGrafos, &qtdArestas);




	
//node_t * head = NULL;
//head = malloc(sizeof(node_t));
//head->val = 1;
//head->next = malloc(sizeof(node_t));



//print_list(head);

	//int qtdGrafos = 9;

	// vetor com todos os grafos
	grafo_t G[qtdGrafos];


	//inicializa o grafo
	for(int i=0; i<qtdGrafos; i++){
		
		G[i].next = NULL;

	}

	int v1, v2;

	//insere as arestas
	for(int i=0; i<qtdArestas; i++){
		fscanf(arqEntrada, "%d %d", &v1, &v2);
		push(G, v1, v2);
		
	}

//imprime
	printf("Lista de Adjacencia\n");
	for(int i=0; i<qtdGrafos; i++){
		printf("[%d]", i);
		print_list(G[i].next);
		printf("\n");
	}
	

//////// comeca o dfs

		//para cada vertice, pintar de branco
		for(int i=0; i<qtdGrafos; i++){
		
			G[i].cor = 'B';
			G[i].pai = -1;
			G[i].val = i;
		}

		tempo = 0;

		//executa o dfs
		for(int i=0; i<qtdGrafos; i++){
		
			if(G[i].cor == 'B'){
				DFS_Visita(G, i);
			}
		}

///////termina dfs

		//imprime os grafos
		printf("\nDetalhes dos Grafos apos DFS\n");
	for(int i=0; i<qtdGrafos; i++){
		printf("Grafo [%d] - cor[%c] - p[%d]\td[%d]\tf[%d]\n", G[i].val, G[i].cor, G[i].pai, G[i].d, G[i].f);

	
		}


//////////calcula a transposta

			// vetor com a transposta
	grafo_t Gt[qtdGrafos];
	//inicializa o grafo
	for(int i=0; i<qtdGrafos; i++){
		
		Gt[i].next = NULL;

	}



	//calcula a transposta
	for(int i=0; i<qtdGrafos; i++){
		
		node_t * current = G[i].next;

	    while (current != NULL) {

	    	push(Gt, current->val, i);
	        current = current->next;
	    }
	}

		//imprime
			printf("\nLista de Adjacencia da Transposta\n");
			for(int i=0; i<qtdGrafos; i++){
				printf("[%d]", i);
				print_list(Gt[i].next);
				printf("\n");
			}
/////////////fim da tansposta


// /////////comeca o segundo dfs

// 		//para cada vertice, pintar de branco
// 		for(int i=0; i<qtdGrafos; i++){
		
// 			Gt[i].cor = 'B';
// 			Gt[i].pai = -1;
// 			Gt[i].val = i;
// 		}

// 		tempo = 0;
// 		int aux, pos;
// 		int min =0, max=999;
// 		//reordenar o vetor
		
// 		for(int k=0;k<qtdGrafos;k++){
// 				for(int i=0;i<qtdGrafos; i++){
					

// 					if(G[i].f > min && G[i].f < max){
// 						aux = G[i].f;
// 						min = G[i].f;
// 						pos = G[i].val;
// 					}

// 				}

// 				max = aux;
// 				min=0;
// 				printf(">>> %d >>%d\n", aux, pos);

// 				node_t * current = Gt[k].next;
// 				Gt[k].next = Gt[pos].next;
// 				printf("saindo do %d e indo pro %d\n", k, pos);
// 				Gt[pos].next = current;

// 				Gt[k].val = pos;
// 				Gt[pos].val = k;

				
// 		}

// 			printf("\n\ntransposta\n");
// 			for(int i=0; i<qtdGrafos; i++){
// 				printf("[%d]", Gt[i].val);
// 				print_list(Gt[i].next);
// 				printf("\n");
// 			}

// 		//executa o dfs no vetor reordenado
// 		for(int i=0; i<qtdGrafos; i++){
		
// 			if(Gt[i].cor == 'B'){
// 				DFS_Visita(Gt, i);
// 			}
// 		}
		

// ///////termina o segundo dfs


//////// comeca o segundo dfs

		//para cada vertice, pintar de branco
		for(int i=0; i<qtdGrafos; i++){
		
			Gt[i].cor = 'B';
			Gt[i].pai = -1;
			Gt[i].val = i;
		}

		tempo = 0;
		imprimeSCC = 1;
		printf("\nComponentes fortemente conexos\n");
		//executa o dfs
		for(int i=qtdGrafos-1; i>=0; i--){
		
			int k=vetorF[i];
			if(Gt[k].cor == 'B'){
				DFS_Visita(Gt, k);
				printf("\n");
			}
		}

///////termina dfs













// for(int i=0; i<qtdGrafos; i++){
// 	printf("%d\n", vetorF[i]);
// }
	

	return;
}