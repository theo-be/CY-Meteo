reset
set terminal png
set output '../data/t2.png'
set datafile separator ","

set key bmargin center horizontal
set title "graphique t2" font ",20"
set xlabel "Date"
set ylabel "Temperature"
set autoscale

plot [*:*] [*:*] '../data/tri_t2.csv' using 1:2 with lines
