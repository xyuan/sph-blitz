#! /bin/bash

#eps solid for solid (not dashed) lines, momochrome (instead of color),... 
#cp ../../src/outdata/prtl$1.dat prtl$1.dat

gnuplot << EOF
set terminal postscript eps enhanced color  "Helvetica" 26


set output "U_profile$1.eps"
set key top left
set grid;
set xlabel "Velocity u"; set ylabel "Position y";
plot [0.0:][0.0:1.0] 'U_line.dat' u 2:1 notitle with line lt -1 lw 0.1, 'prtl$1.dat' u 3:2 notitle lt 1 with points;

set terminal png large
set output "U_profile$1.png"
replot

reset

set terminal postscript eps enhanced color  "Helvetica" 26

set output "T_profile$1.eps"
set key top left
set grid;
set xlabel "Temperature T"; set ylabel "Position y";
plot [:][0.0:1.0] 'prtl$1.dat' u 6:2 notitle lt 1 with points;

set terminal png large
set output "T_profile$1.png"
replot

reset

EOF