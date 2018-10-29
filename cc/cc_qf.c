#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "comum.h"

// retorna o minimo entre dois valores
#define MINIMO(x, y) (((x) < (y)) ? (x) : (y))

void union_(int *vetorQF, int qtdVertices, int p, int q);
int find_(int *vetorQF, int p);

int main() {
	int **matrizEntrada, *vetorQF, qtdVertices, qtdArestas;
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
	vetorQF = (int *)malloc(qtdVertices * sizeof(int));

	// inicizaliza o vetor, cada vertice é seu proprio pai
	for(int i=0; i<qtdVertices; i++) {
		vetorQF[i] = i;
	}

	// para cada aresta, ler o arquivo e chamar union
	for(int i=1; i<qtdArestas; i++) {
		union_(vetorQF, qtdVertices, matrizEntrada[i][0], matrizEntrada[i][1]);
	}

	// termina de contar o tempo
	tempo_final = clock();
	tempo_total = (double)(tempo_final - tempo_inicial) / CLOCKS_PER_SEC;
	printf("%.4lf\n", tempo_total);

	//imprimeSaida("saida_qf.txt", vetorQF, qtdVertices);

	// libera memoria
	free(vetorQF);
	free(matrizEntrada);

	return 0;
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

	// faz union de dois vertices
	// percorre o vetor para atualiar todos os pais
	for(int i=0; i<qtdVertices; i++) {
		if(vetorQF[i] == pID || vetorQF[i] == qID) {
			// da o minimo para o pai por motivos de padronizacao
			vetorQF[i] = MINIMO(pID, qID);
		}
	}
}