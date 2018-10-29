for i in $(seq 0 0.01 1);
	do
	{
		./cc_grama g$i.txt >> tempo_grama.txt
	}
done