cc:
	clear
	@echo "-> Gerando grafo aleatório..."
	gcc geradorGrafo.c
	./a.out > grafo.txt
	@echo "-> Componentes Conexos - DFS"
	gcc -fopenmp cc_dfs.c
	./a.out
	@echo "-> Componentes Conexos - Grama"
	gcc -fopenmp cc_grama.c -lm -Wall
	./a.out