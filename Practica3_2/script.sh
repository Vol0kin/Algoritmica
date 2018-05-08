#!/bin/bash

g++ dif_long.cpp -o dif_long
g++ tsp.cpp -o tsp

nombre=./datosTSP/$1
datos="$nombre.tsp"
optimo="$nombre.opt.tour"
./version2 $datos > temp1.txt

./tsp $datos $optimo > "cam_opt.txt"
./tsp $datos "temp1.txt" > "cam_prop.txt"
./dif_long $datos $optimo "temp1.txt"
gnuplot -e "set terminal png; set output 'optimo.png'; plot 'cam_opt.txt' using 2:3 with lines title 'CaminoOptimo' ; set output 'propio.png'; plot 'cam_prop.txt'  using 2:3 with lines title 'CaminoPropio'; quit;"

rm "temp1.txt" "cam_opt.txt" "cam_prop.txt"
