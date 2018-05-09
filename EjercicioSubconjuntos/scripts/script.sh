#!/bin/bash

echo "" > data/fbruta_28.dat
echo "" > data/backinf_28.dat
echo "" > data/backsinf_28.dat


for ((N=5;N<=28;N=N+1))
do
    BUSQUEDA=$((N+1))
    bin/fbruta $N $BUSQUEDA >> data/fbruta_28.dat
    bin/backsinf $N $BUSQUEDA >> data/backsinf_28.dat
    bin/backinf $N $BUSQUEDA >> data/backinf_28.dat
done

cp data/backsinf_28.dat data/backsinf_50.dat
cp data/backinf_28.dat data/backinf_50.dat

for ((N=29;N<=50;N=N+1))
do
    BUSQUEDA=$((N+1))
    bin/backsinf $N $BUSQUEDA >> data/backsinf_50.dat
    bin/backinf $N $BUSQUEDA >> data/backinf_50.dat
done

gnuplot -e "set xlabel 'Tamanio'; set ylabel 'Tiempo'; set terminal png; \
            set output 'screenshots/comparacion_3.png'; plot 'data/fbruta_28.dat' with lines title 'Fuerza bruta', 'data/backsinf_28.dat' with lines title 'Backtracking sin info.', 'data/backinf_28.dat' with lines title 'Backtracking con info.'; \
            set output 'screenshots/fbruta_28.png'; plot 'data/fbruta_28.dat' with lines title 'Fuerza Bruta'; \
            set output 'screenshots/comparacion_back_28.png'; plot 'data/backsinf_28.dat' with lines title 'Backtracking sin info.', 'data/backinf_28.dat' with lines title 'Backtracking con info.'; \
            set output 'screenshots/comparacion_back_50.png'; plot 'data/backsinf_50.dat' with lines title 'Backtracking sin info.', 'data/backinf_50.dat' with lines title 'Backtracking con info.'; quit;"

