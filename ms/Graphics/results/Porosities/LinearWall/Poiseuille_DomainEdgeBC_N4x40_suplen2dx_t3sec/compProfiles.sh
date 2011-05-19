#! /bin/bash

#eps solid for solid (not dashed) lines, momochrome (instead of color),... 
#cp ../../src/outdata/prtl$1.dat prtl$1.dat

gnuplot << EOF
set terminal postscript eps enhanced color  "Helvetica" 26

set output "U_profiles$1.eps"

set key 0.006,0.07
set grid;
set xlabel "Velocity u"; set ylabel "Position y";
plot [0.0:][-0.5:0.5]  'exact$1.dat' u 2:1 title 'Exact' with line lt 2 lw 8,'simuForPlot$1.dat' u 2:1 title 'Simulation'  with points lt 1 lw 8;

set terminal png large
set output "U_profiles$1.png"
replot

reset

EOF