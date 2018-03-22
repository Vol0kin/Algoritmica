#!/bin/csh -vx

echo "" > tiempos_mergesort.dat
@ i = 100
while ( $i < 100000 )
	./mergesort $i >> tiempos_mergesort.dat
	@ i += 1500
end

