reset
set terminal png
set output '../data/p2.png'
set datafile separator ","

set key bmargin center horizontal
set title "Graphique p2" font ",20"
set xlabel "Date"
set ylabel "Pression moyenne"
set xrange [*:*]
set yrange [*:*]
set autoscale

plot '../data/tri_p2.csv' using 1:2 with lines
