#include <stdio.h>
#include <stdlib.h>

#define MINIMO(x, y) (((x) < (y)) ? (x) : (y))

void union_(int *vetorQF, int qtdVertices, int p, int q);
int find_(int *vetorQF, int p);

void main() {
	FILE *arqEntrada;
	FILE *arqSaida;
	arqEntrada = fopen("grafo.txt", "r");
  	arqSaida = fopen ("result_QF.txt","w");
	int *vetorQF, qtdVertices, qtdArestas, p, q; 

	// le a quantidade de vertices e de arestas
	fscanf(arqEntrada, "%d %d", &qtdVertices, &qtdArestas);

	// aloca espaco para o vetor dos componentes
	vetorQF = (int *)malloc(qtdVertices * sizeof(int));

	// inicizaliza o vetor, cada vertice é seu proprio pai
	for(int i=0; i<qtdVertices; i++) {
		vetorQF[i] = i;
	}

	// para cada aresta, ler o arquivo e chamar union
	for(int i=0; i<qtdArestas; i++) {
		fscanf(arqEntrada, "%d %d", &p, &q);
		union_(vetorQF, qtdVertices, p, q);
	}

	// imprime o vetor no arquivo de saida
	for(int i=0; i<qtdVertices; i++) {
		//fprintf(arqSaida, "%d %d\n", i, vetorQF[i]);
		printf("%d %d\n", i, vetorQF[i]);
	}

	// libera memoria
	free(vetorQF);
	return;
}

// retorna o pai atual de um vertice do vetor
int find_(int *vetorQF, int p) {
	return vetorQF[p];
}

// faz union de dois vertices
void union_(int *vetorQF, int qtdVertices, int p, int q) {
	int pID = find_(vetorQF, p);
	int qID = find_(vetorQF, q);

	// se os pais sao iguais, ja estao no mesmo componente
	if(pID == qID)
		return;
	int menor = 0;
	// faz uniao de dois vertices
	// percorre o vetor para atualiar todos os pais
	for(int i=0; i<qtdVertices; i++) {
		if(vetorQF[i] == pID || vetorQF[i] == qID) {
			vetorQF[i] = MINIMO(pID, qID);
		}
	}
}