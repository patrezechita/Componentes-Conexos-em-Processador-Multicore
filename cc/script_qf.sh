for i in $(seq 0 0.01 1);
	do
	{
		./cc_qf g$i.txt >> tempo_qf.txt
	}
done