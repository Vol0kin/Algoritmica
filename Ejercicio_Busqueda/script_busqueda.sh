#!/bin/csh -vx

echo "" > tiempo_bternaria.dat
@ i = 100
while ( $i < 1000000 )
    ./busqueda $i >> tiempo_bternaria.dat
    @ i += 10000
end

