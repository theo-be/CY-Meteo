reset
set terminal png
set output '../data/vent.png'
set datafile separator ","

set key bmargin center horizontal
set title "Graphique vent" font ",20"
set xlabel "Longitude"
set ylabel "Latitude"
set xrange [*:*]
set yrange [*:*]
set autoscale

plot '../data/tri_vent.csv' using 4:3:(cos(column(1))*column(2)):(sin(column(1))*column(2)) w vec


