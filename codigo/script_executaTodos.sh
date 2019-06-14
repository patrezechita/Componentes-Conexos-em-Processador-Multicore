declare -a densidade=("0.05" "0.25" "0.50" "0.75" "1.0")
declare -a grafo=("5000" "10000" "15000" "25000")

## geraGrafo
for i in "${densidade[@]}"
do
	for j in "${grafo[@]}"
	do
		./geraGrafo $j $i > "g${j}d${i}.txt"
	done
done

## cc_grama 2 threads
for i in "${densidade[@]}"
do
	for j in "${grafo[@]}"
	do
		./cc_grama "g${j}d${i}.txt" 2 >> tempo.txt
	done
done

## cc_grama 4 threads
for i in "${densidade[@]}"
do
	for j in "${grafo[@]}"
	do
		./cc_grama "g${j}d${i}.txt" 4 >> tempo.txt
	done
done

## cc_grama 8 threads
for i in "${densidade[@]}"
do
	for j in "${grafo[@]}"
	do
		./cc_grama "g${j}d${i}.txt" 8 >> tempo.txt
	done
done

## cc_grama 16 threads
for i in "${densidade[@]}"
do
	for j in "${grafo[@]}"
	do
		./cc_grama "g${j}d${i}.txt" 16 >> tempo.txt
	done
done