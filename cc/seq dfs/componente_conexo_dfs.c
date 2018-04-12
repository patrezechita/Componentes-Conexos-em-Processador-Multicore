#include <stdio.h>
#include <stdlib.h>

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
int vetorDFS[999];

void push(grafo_t G[], int val1, int val2);
void DFS_Visita(grafo_t G[], int i);

void main() {
	FILE *arqEntrada;
	arqEntrada = fopen("grafo.txt", "r");

	int qtdVertices, qtdArestas;

	// guarda o tamanho da matriz quadrada
	fscanf(arqEntrada, "%d %d", &qtdVertices, &qtdArestas);

	// vetor com todos os grafos
	grafo_t G[qtdVertices];

	//inicializa o grafo
	for(int i=0; i<qtdVertices; i++) {	
		G[i].next = NULL;
	}

	int v1, v2;

	//insere as arestas
	for(int i=0; i<qtdArestas; i++){
		fscanf(arqEntrada, "%d %d", &v1, &v2);
		push(G, v1, v2);
		push(G, v2, v1);
	}
	

//////// comeca o dfs

		//para cada vertice, pintar de branco
		for(int i=0; i<qtdVertices; i++){
		
			G[i].cor = 'B';
			G[i].pai = -1;
			G[i].val = i;
		}

		
				
	

		//executa o dfs
		for(int i=0; i<qtdVertices; i++){
		
			if(G[i].cor == 'B'){
				root = i;
				DFS_Visita(G, i);
			}
		}

		for(int i=0; i<qtdVertices; i++){
			printf("%d %d\n", i, vetorDFS[i]);
		}

	return;
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