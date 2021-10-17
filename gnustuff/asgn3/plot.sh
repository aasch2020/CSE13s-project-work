#!/usr/bin/env bash

make clean && make

# Split each line using comma as the delimiter.
# Then extract x, the computed value, and the library value from each line.
# Output to `sine()` results to `/tmp/computed.dat`.
# Output to `sin()` results to `/tmp/library.dat`.
./sorting -a | awk -F, '{
    split($1, heap, " ");
    split(heap[1], x, "[()]")
    split($2, shell, " ");
    print x[2], heap[3] > "/tmp/computed.dat"
    print x[2], shell[3] > "/tmp/library.dat"
}'

echo -n "Plotting... "
gnuplot <<EOF
set terminal pdf
set key outside
set zeroaxis

set output "comparison.pdf"
set title "Insert vs. Shell vs. Heap vs. Quick"
plot "/tmp/computed.dat" with lines title "Heap", \
    "/tmp/library.dat" with lines title "Quick"
EOF
echo "done."
