cc:
	clear
	@echo "-> Gerando grafo aleatório..."
	gcc geradorGrafo.c
	./a.out > grafo.txt
	@echo "-> Componentes Conexos - DFS"
	gcc -fopenmp cc_dfs.c
	./a.out
	@echo "-> Componentes Conexos - QUICKFIND"
	gcc -fopenmp cc_qf.c
	./a.out
	@echo "-> Componentes Conexos - Grama"
	gcc -fopenmp cc_grama.c -lm
	./a.out