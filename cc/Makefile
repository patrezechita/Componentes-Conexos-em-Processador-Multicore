cc:
	clear
	@echo "-> Gerando grafo aleatório..."
	gcc geradorGrafo.c
	./a.out > grafo.txt
	@echo "-> Componentes Conexos - QuickFind"
	gcc cc_qf.c
	./a.out
	@echo "-> Componentes Conexos - DFS"
	gcc cc_dfs.c
	./a.out
	@echo "-> Componentes Conexos - Grama"
	gcc -fopenmp cc_grama.c -lm -Wall
	./a.out


	@echo "-> Comparando as saidas..."
	diff saida_qf.txt saida_dfs.txt
	diff saida_qf.txt saida_grama.txt
	diff saida_dfs.txt saida_grama.txt