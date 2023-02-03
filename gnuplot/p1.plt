reset
set terminal png
set output '../data/p1.png'
set datafile separator ","

set key bmargin center horizontal
set title "Graphique p1" font ",20"
set xlabel "Id station"
set ylabel "Pression moyenne, min, max"
set autoscale
Shadecolor = "#80E0A080"

# set colorbox vertical origin screen 0.9, 0.2 size screen 0.05, 0.6 front  noinvert bdefault

#plot [*:*] [*:*] '../test/tri_p1.csv' using 1:2:3 with yerrorbars

plot '../data/tri_p1.csv' using 1:3:4 with filledcurve fc rgb Shadecolor title "Pression minimum et maximum", '' using 1:2 smooth mcspline title "Pression moyenne"



# pause 5