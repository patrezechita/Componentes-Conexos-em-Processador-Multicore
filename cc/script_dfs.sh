for i in $(seq 0 0.01 1);
	do
	{
		./cc_dfs g$i.txt >> tempo_dfs.txt
	}
done