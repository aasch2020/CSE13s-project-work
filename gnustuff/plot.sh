#!/usr/bin/env bash

make clean && make

# Split each line using comma as the delimiter.
# Then extract x, the computed value, and the library value from each line.
# Output to `sine()` results to `/tmp/computed.dat`.
# Output to `sin()` results to `/tmp/library.dat`.
./mathlib-test -r | awk -F, '{
    split($1, computed, " ");
    split(computed[1], x, "[()]")
    split($2, library, " ");
    print x[2], computed[3] > "/tmp/computed.dat"
    print x[2], library[3] > "/tmp/library.dat"
}'

echo -n "Plotting... "
gnuplot <<EOF
set terminal pdf
set key outside
set zeroaxis

set output "eulerpi3.pdf"
set title "Euler vs. M PI"
plot "/tmp/computed.dat" with linespoints title "Euler", \
    "/tmp/library.dat" with linespoints title "M PI"
EOF
echo "done."
