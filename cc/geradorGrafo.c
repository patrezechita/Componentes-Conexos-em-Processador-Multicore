#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 

// recebe o número de vértices e a densidade do número de arestas
// densidade varia de 0 a 1
int main(int argc, char *argv[]) 
{ 
	int **vetorArestas;
	int qtdVertices, qtdArestas, num1, num2, i, j, sai;
	float densidade, qtdVerticesFinal;

	srand(time(0));
	
	// cálculo da quantidade de arestas a serem processadas
	qtdVertices = atoi(argv[1]);
	densidade = atof(argv[2]);
	qtdVerticesFinal = qtdVertices * densidade;
	qtdArestas = (qtdVerticesFinal*(qtdVerticesFinal-1))/2;

	// aloca memória para o vetor com arestas
	vetorArestas = malloc(qtdArestas * sizeof(int *));
	for(int i=0; i<qtdArestas; i++)
	{
		vetorArestas[i] = malloc(2 * sizeof(int));
	}

	i = 0;
	while(i < qtdArestas)
	{
		// gera dois números aleatórios
		num1 = rand() % qtdVertices;
		num2 = rand() % qtdVertices;

		sai=0;
		// se os números forem iguais, não guardar
		if(num1 != num2)
		{	
			// percorre o vetor procurando se esses números já foram colocados
			for(j=0; j<=i; j++)
			{
				// se já estão no vetor, não guardar
				if((vetorArestas[j][0] == num1 && vetorArestas[j][1] == num2) || (vetorArestas[j][0] == num2 && vetorArestas[j][1] == num1))
				{	
					sai = 1;
					break;
				}
			}

			// se não foram achados, então guardar
			if(sai == 0)
			{
				vetorArestas[i][0] = num1;
				vetorArestas[i][1] = num2;
				i++;
			}
		}
	} 

	// imprime o vetor de arestas
	printf("%d %d\n", qtdVertices, qtdArestas);
	for (i = 0; i < qtdArestas; i++) { 
		printf("%d ", vetorArestas[i][0]);
		printf("%d\n", vetorArestas[i][1]);
	}

	// desaloca vetor da memória
	for(int i=0; i<qtdArestas; i++)
	{
		free(vetorArestas[i]);
	}
	free(vetorArestas);

	return 0; 
}