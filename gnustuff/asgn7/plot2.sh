#!/usr/bin/env bash

for i in $(seq 1 1000 1000000)
do
	echo $i >> axes.txt
	./banhammer -s -t $i < inputtxt
done
