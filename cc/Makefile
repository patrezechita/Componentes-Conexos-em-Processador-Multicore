cc:
	@echo "-> Gerando grafo aleatório..."
	gcc geradorGrafo.c -Wall
	./a.out 1000 0.50 > grafo.txt
	@echo "-> Componentes Conexos - QuickFind"
	gcc cc_qf.c
	tput setaf 1; time ./a.out; tput sgr0;
	@echo "-> Componentes Conexos - DFS"
	gcc cc_dfs.c
	tput setaf 1; time ./a.out; tput sgr0;
	@echo "-> Componentes Conexos - Grama"
	gcc -fopenmp cc_grama.c -lm -Wall
	tput setaf 1; time ./a.out; tput sgr0;

	@echo "-> Comparando as saidas..."
	diff saida_qf.txt saida_dfs.txt
	diff saida_qf.txt saida_grama.txt
	diff saida_dfs.txt saida_grama.txt