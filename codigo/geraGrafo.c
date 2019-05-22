#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 

// recebe o número de vértices e a densidade do número de arestas
// densidade varia de 0 a 1
int main(int argc, char *argv[]) 
{ 
	int **vetorArestas;
	int i, j, r, aux, aux1, aux2;
	int qtdVertices, qtdArestasPossiveis, qtdArestasDesejadas;
	float densidade;
	
	// recebe os argumentos
	qtdVertices = atoi(argv[1]);
	densidade = atof(argv[2]);
	
	// se a densidade for 0, então queremos um grafo árvore
	// número de vértices iguais ao número de arestas
	if(densidade == 0.0)
	{
		qtdArestasPossiveis = (qtdVertices*(qtdVertices-1))/2;
		qtdArestasDesejadas = qtdVertices;
	}

	// do contrário, calcula normalmente as arestas
	else
	{
		qtdArestasPossiveis = (qtdVertices*(qtdVertices-1))/2;
		qtdArestasDesejadas = qtdArestasPossiveis * densidade;
	}

	// alocação de memória para o vetor com as arestas
	vetorArestas = malloc(qtdArestasPossiveis * sizeof(int *));
	for(int i=0; i<qtdArestasPossiveis; i++)
	{
		vetorArestas[i] = malloc(2 * sizeof(int));
	}

	// gera todas as combinações de pares de arestas no vetorAresta
	aux = 0;
	for(i=0; i<qtdVertices; i++)
	{
		for(j=i+1; j<qtdVertices; j++)
		{
			vetorArestas[aux][0] = i;
			vetorArestas[aux][1] = j;
			aux++;
		}
	}

	// troca aleatóriamente o índice de todas as N primeiras posições
	// sendo N o número de arestas desejadas
	// srand(time(0));
	srand(424242); //pra gerar o mesmo grafo sempre
	for (i = 0; i < qtdArestasDesejadas; i++)
	{ 
		r = rand() % qtdArestasPossiveis;

		aux1 = vetorArestas[i][0];
		aux2 = vetorArestas[i][1];

		vetorArestas[i][0] = vetorArestas[r][0];
		vetorArestas[i][1] = vetorArestas[r][1];

			// somente para inverter a ordem as vezes
			if((rand() % 2 ) == 0)
			{
				vetorArestas[r][0] = aux1;
				vetorArestas[r][1] = aux2;	
			}
			else
			{
				vetorArestas[r][0] = aux2;
				vetorArestas[r][1] = aux1;	
			}
	}

	// imprime as N primeiras arestas
	printf("%d %d\n", qtdVertices, qtdArestasDesejadas);
	for (i = 0; i < qtdArestasDesejadas; i++)
	{ 
		printf("%d ", vetorArestas[i][0]);
		printf("%d\n", vetorArestas[i][1]);
	}

	// desaloca vetorArestas da memória
	for(int i=0; i<qtdArestasPossiveis; i++)
	{
		free(vetorArestas[i]);
	}
	free(vetorArestas);

	return 0; 
}