declare -a densidade=("0.0" "0.33" "0.66" "1.0")
declare -a grafo=("1000")

## geraGrafo
for i in "${densidade[@]}"
do
	for j in "${grafo[@]}"
	do
		./geraGrafo $j $i > "g${j}d${i}.txt"
	done
done

## cc_dfs
for i in "${densidade[@]}"
do
	for j in "${grafo[@]}"
	do
		./cc_dfs "g${j}d${i}.txt" >> tempo.txt
	done
done

## cc_qf
for i in "${densidade[@]}"
do
	for j in "${grafo[@]}"
	do
		./cc_qf "g${j}d${i}.txt" >> tempo.txt
	done
done

## cc_grama
for i in "${densidade[@]}"
do
	for j in "${grafo[@]}"
	do
		./cc_grama "g${j}d${i}.txt" >> tempo.txt
	done
done
