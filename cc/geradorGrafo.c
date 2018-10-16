#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 

void printRandoms(int lower, int upper, int count) 
{ 
	int i; 
	for (i = 0; i < count; i++) { 
		int num1 = (rand() % (upper - lower + 1)) + lower; 
		printf("%d ", num1);
		int num2 = (rand() % (upper - lower + 1)) + lower; 
		printf("%d\n", num2); 
	} 
} 


int main() 
{ 
	int lower = 5, upper = 50, count = 9; 


	srand(time(0)); 



	int qtdVertices = 1200;
	int qtdArestas = qtdVertices;
	printf("%d %d\n", qtdVertices, qtdArestas);

	printRandoms(0, qtdVertices-1, qtdArestas); 


	return 0; 
} 