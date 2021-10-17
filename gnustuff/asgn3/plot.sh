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
    split($3, insert, " ");
    split($4, quick, " ");

    print x[2], heap[3] > "/tmp/heap.dat"
    print x[2], shell[3] > "/tmp/shell.dat"
    print x[2], insert[3] > "/tmp/insert.dat"
    print x[2], quick[3] > "/tmp/quick.dat"
}'

echo -n "Plotting... "
gnuplot <<EOF
set terminal pdf
set key outside
set zeroaxis

set output "LessDomainMoves.pdf"
set title "Insert vs. Shell vs. Heap vs. Quick"
plot "/tmp/heap.dat" with lines title "Heap", \
    "/tmp/shell.dat" with lines title "Shell", \
    "/tmp/insert.dat" with lines title "Insert", \
    "/tmp/quick.dat" with lines title "Quick"
EOF
echo "done."
