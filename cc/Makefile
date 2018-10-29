cc:
	gcc geraGrafo.c -o geraGrafo -Wall
	./geraGrafo 500 0.5 > grafo.txt

	gcc cc_qf.c -o cc_qf -Wall
	./cc_qf grafo.txt

	gcc cc_dfs.c -o cc_dfs -Wall
	./cc_dfs grafo.txt

	gcc -fopenmp cc_grama.c -o cc_grama -lm -Wall
	./cc_grama grafo.txt