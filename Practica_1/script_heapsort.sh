#!/bin/csh -vx

echo "" > tiempos_heapsort.dat
@ i = 100
while ( $i < 100000 )
	./heapsort $i >> tiempos_heapsort.dat
	@ i += 1500
end

