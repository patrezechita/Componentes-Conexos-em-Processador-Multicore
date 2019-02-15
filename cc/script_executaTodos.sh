declare -a densidade=("0.10" "0.25" "0.50" "0.75" "1.00")
declare -a grafo=("500")

## geraGrafo
for i in "${densidade[@]}"
do
	for j in "${grafo[@]}"
	do
		./geraGrafo $j $i > "g$j d$i.txt"
	done
done

## cc_dfs
for i in "${densidade[@]}"
do
	for j in "${grafo[@]}"
	do
		./cc_dfs "g$j d$i.txt" >> tempo.txt
	done
done

## cc_qf
for i in "${densidade[@]}"
do
	for j in "${grafo[@]}"
	do
		./cc_qf "g$j d$i.txt" >> tempo.txt
	done
done

## cc_grama
for i in "${densidade[@]}"
do
	for j in "${grafo[@]}"
	do
		./cc_grama "g$j d$i.txt" >> tempo.txt
	done
done
