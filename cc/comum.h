int **lerEntrada(char nomeEntrada[]) {
	int **matrizEntrada, qtdVertices, qtdArestas;
	FILE *arqEntrada;
	arqEntrada = fopen(nomeEntrada, "r");
	
	// le a quantidade de vertices e de arestas
	fscanf(arqEntrada, "%d %d", &qtdVertices, &qtdArestas);
	qtdArestas++;

	// aloca memoria para a matriz Nx2
	matrizEntrada = malloc(qtdArestas * sizeof(int *));
	for (int i = 0; i < qtdArestas; i++) {
		matrizEntrada[i] = malloc(2 * sizeof(int));
	}

	// coloca de volta a primeira linha
	matrizEntrada[0][0] = qtdVertices;
	matrizEntrada[0][1] = qtdArestas;

	// le o resto do arquivo
	for(int i=1; i<qtdArestas; i++) {
		fscanf(arqEntrada, "%d %d", &matrizEntrada[i][0], &matrizEntrada[i][1]);
	}

	return matrizEntrada;
}

void imprimeSaida(char nomeSaida[], int vetorSaida[], int tamVetor) {
	FILE *arqSaida;
	arqSaida = fopen (nomeSaida,"w");
	int vetorQtdCC[tamVetor], cc;

	// preenche o vetor auxiliar com 0
	for(int i=0; i<tamVetor; i++) {
		vetorQtdCC[i]=0;
	}

	// da 1 para cada indice que achar
	for(int i=0; i<tamVetor; i++) {
		vetorQtdCC[vetorSaida[i]]=1;
	}

	// conta os indices, sera o numero de componentes
	cc = 0;
	for(int i=0; i<tamVetor; i++) {
		if(vetorQtdCC[i]==1) {
			cc++;
		}
	}

	// imprime a quantidade de componentes
	fprintf(arqSaida, "%d\n", cc);

	// imprime o vetor no arquivo de saida
	for(int i=0; i<tamVetor; i++) {
		fprintf(arqSaida, "%d %d\n", i, vetorSaida[i]);
	}
}