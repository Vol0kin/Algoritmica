#!/bin/csh -vx

echo "" > tiempos_quicksort_vladislav.dat
@ i = 100
while ( $i < 100000 )
	./quicksort $i >> tiempos_quicksort_vladislav.dat
	@ i += 500
end

