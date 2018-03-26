#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int G[999];

int find_(int p){
	return G[p];
}

void union_(int p, int q){

	int pID = find_(p);
	int qID = find_(q);

	if(pID == qID)
		return;
	
	for(int i=0; i<999; i++){
		
		
		if(G[i] == pID){
			G[i] = qID;
		}

	}


}

bool conectado(int p, int q){

	if(find_(p) == find_(q))
		return true;
	else
		return false;

}



void main() {

	FILE *arqEntrada;
	arqEntrada = fopen("grafo.txt", "r");



	if (arqEntrada == NULL) {
		printf("Arquivo nao encontrado.\n");
		exit(0);
	}


	int qtdGrafos, qtdArestas;


	fscanf(arqEntrada, "%d %d", &qtdGrafos, &qtdArestas);

	


	//inicializa o vetor
	for(int i=0; i<qtdGrafos; i++){
		
		G[i] = i;

	}

	int p, q;
	for(int i=0; i<qtdArestas; i++){
		fscanf(arqEntrada, "%d %d", &p, &q);
		if(conectado(p, q)==true){

		}
		else
			union_(p, q);
		
	}


		for(int i=0; i<qtdGrafos; i++){
		
		printf("%d ", i);

		}

		printf("\n");


		for(int i=0; i<qtdGrafos; i++){
		
		printf("%d ", G[i]);

		}

		printf("\n");


	return;
}