#!/usr/bin/env bash

echo -n "Plotting... "
gnuplot <<EOF
set terminal pdf
set key outside
set zeroaxis
set output "ht1.pdf"
set title "Bloom Filter Load as HT size changes"
plot "htbflode.dat" with lines title "BF load", \
   
EOF
echo "done."
