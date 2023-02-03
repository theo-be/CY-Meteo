reset
set terminal png
set output '../data/altitude.png'
set datafile separator ","

set xyplane relative 0

set key top
set title "Graphique altitude" font ",20"
set xlabel "Longitude"
set ylabel "Latitude"
set zlabel "Altitude"
set autoscale noextend
set pm3d map interpolate 6,6 flush begin nohidden3d
set palette rgbformulae 30,31,32
set dgrid3d 20,20

set view map scale 1
set xrange [*:*]
set yrange [*:*]
set zrange [*:*]
set xyplane relative 0

unset surface
set pm3d at st
set palette color positive

set colorbox vertical origin screen 0.9, 0.2 size screen 0.05, 0.6 front  noinvert bdefault

splot '../data/tri_altitude.csv' using 3:2:1 with pm3d
