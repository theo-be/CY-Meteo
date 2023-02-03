reset
set terminal png
set output '../data/humidite.png'

set xyplane relative 0
set datafile separator ","
set title "Graphique humidite" font ",20"
set xlabel "Longitude"
set ylabel "Latitude"
set autoscale noextend
set xrange [*:*]
set yrange [*:*]
set pm3d map interpolate 6,6 flush begin nohidden3d
set palette rgbformulae 30,31,32
set dgrid3d 20,20

set colorbox vertical origin screen 0.9, 0.2 size screen 0.05, 0.6 front noinvert bdefault

splot '../data/tri_humidite.csv' using 4:3:1 with pm3d

# pause 5