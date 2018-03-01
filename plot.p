set terminal png
set output "graph.png"
set xlabel "eps"
set ylabel "alpha"
set zlabel "err"
set view map
set size ratio .9

set object 1 rect from graph 0, graph 0 to graph 1, graph 1 back
set object 1 rect fc rgb "black" fillstyle solid 1.0

splot "stats.txt" using 1:2:3 with points pointtype 5 pointsize 1 palette linewidth 10

#splot "stats.txt" using 1:2:3 #with lines
