v=500
for i in $(seq 0 0.01 1);
	do
	{
		./geraGrafo $v $i > g$v-$i.txt
	}
done