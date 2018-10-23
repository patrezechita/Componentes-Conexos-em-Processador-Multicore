#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 

// recebe o número de vértices e a densidade do número de arestas
// densidade varia de 0 a 1
int main(int argc, char *argv[]) 
{ 
	int **vetorArestas, **vetorCompleto;
	int qtdVertices, qtdArestas, qtdArestasTotal, i, j, aux, num;
	float densidade, qtdVerticesFinal;

	srand(time(0));
	
	// cálculo da quantidade de arestas a serem processadas
	qtdVertices = atoi(argv[1]);
	densidade = atof(argv[2]);
	qtdVerticesFinal = qtdVertices * densidade;
	qtdArestasTotal = (qtdVertices*(qtdVertices-1))/2;
	qtdArestas = (qtdVerticesFinal*(qtdVerticesFinal-1))/2;

	// aloca memória para o vetor com arestas
	vetorArestas = malloc(qtdArestas * sizeof(int *));
	for(int i=0; i<qtdArestas; i++)
	{
		vetorArestas[i] = malloc(2 * sizeof(int));
	}

	// aloca memória para o vetor auxiliar
	vetorCompleto = malloc(qtdArestasTotal * sizeof(int *));
	for(int i=0; i<qtdArestasTotal; i++)
	{
		vetorCompleto[i] = malloc(2 * sizeof(int));
	}

	// gera todas as combinações de pares de arestas
	// e povoa vetorCompleto
	aux = 0;
	for(i=0; i<qtdVertices; i++)
	{
		for(j=i+1; j<qtdVertices; j++)
		{
			vetorCompleto[aux][0] = i;
			vetorCompleto[aux][1] = j;
			aux++;
		}
	}

	// escolhe uma posição aleatória de vetorCompleto
	// e dá para o vetorAresta; caso já tenha pego
	// ignorar e gerar outra posição aleatória
	i=0;
	while(i<qtdArestas)
	{
		num = rand() % qtdArestasTotal;
		if(vetorCompleto[num][0] != -1)
		{
			// somente para inverter a ordem as vezes
			if((rand()%2)==0)
			{
				vetorArestas[i][0] = vetorCompleto[num][0];
				vetorArestas[i][1] = vetorCompleto[num][1];
			}
			else
			{
				vetorArestas[i][0] = vetorCompleto[num][1];
				vetorArestas[i][1] = vetorCompleto[num][0];
			}

			vetorCompleto[num][0] = -1;
			i++;
		}
	}

	// imprime o vetor de arestas
	printf("%d %d\n", qtdVertices, qtdArestas);
	for (i = 0; i < qtdArestas; i++) { 
		printf("%d ", vetorArestas[i][0]);
		printf("%d\n", vetorArestas[i][1]);
	}

	// desaloca vetorAresta da memória
	for(int i=0; i<qtdArestas; i++)
	{
		free(vetorArestas[i]);
	}
	free(vetorArestas);

	// desaloca vetorCompleto da memória
	for(int i=0; i<qtdArestasTotal; i++)
	{
		free(vetorCompleto[i]);
	}
	free(vetorCompleto);

	return 0; 
}