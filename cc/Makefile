cc:
	clear
	@echo "> GERA GRAFO"
	gcc geradorGrafo.c -Wall
	./a.out 1000 0.5 > grafo.txt

	@echo ">>> QF SEQUENCIAL"
	gcc cc_qf.c -Wall
	./a.out
	@echo ">>> DFS SEQUENCIAL"
	gcc cc_dfs.c -Wall
	./a.out
	@echo ">>> GRAMA"
	gcc -fopenmp cc_grama.c -lm -Wall
	./a.out

	@echo "> COMPARANDO SAIDAS"
	diff saida_qf.txt saida_dfs.txt
	diff saida_qf.txt saida_grama.txt
	diff saida_dfs.txt saida_grama.txt