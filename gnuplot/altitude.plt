reset


set terminal png
set output '../data/altitude.png'
set datafile separator ","



# set style data lines
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

# set border 4095 front lt black linewidth 1.000 dashtype solid
# set view map scale 1
set xrange [*:*]
set yrange [*:*]
set zrange [*:*]
set xyplane relative 0
#set samples 25
#set isosamples 20

unset surface
set pm3d at st
set palette color positive

# splot sin(sqrt(x**2+y**2))/sqrt(x**2+y**2)

set colorbox vertical origin screen 0.9, 0.2 size screen 0.05, 0.6 front  noinvert bdefault




splot '../data/tri_altitude.csv' using 3:2:1 with pm3d



# set colorbox vertical origin screen 0.9, 0.2 size screen 0.05, 0.6 front  noinvert bdefault

# plot [*:*] [*:*] '../test/tri_altitude.csv' using 3:2 with points

