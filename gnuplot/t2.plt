reset
set terminal png
set output '../data/t2.png'
set datafile separator ","

set key bmargin center horizontal
set title "graphique t2" font ",20"
set xlabel "date"
set ylabel "temperature"
set autoscale

# set colorbox vertical origin screen 0.9, 0.2 size screen 0.05, 0.6 front  noinvert bdefault

plot [*:*] [*:*] '../data/tri_t2.csv' using 1:2 with lines

# pause 5