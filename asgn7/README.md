# Assignment 7 The Great Firewall of UCSC
The given files read an censor the given input using a bloom filter and hash table, with binary search trees. This file reads in badspeak and newspeak files to build a censoring database of unallowed words, and then censores the standard input with those words.
## Run the following to build the programs:
```
$ make
```
## Running
```
./banhammer -args
```
SYNOPSIS
  A word filtering program for the GPRSC.
  Filters out and reports bad words parsed from stdin.

USAGE
  ./banhammer [-hs] [-t size] [-f size]

OPTIONS
  -h           Program usage and help.
  -s           Print program statistics.
  -t size      Specify hash table size (default: 2^16).
  -f size      Specify Bloom filter size (default: 2^20).
```

                                                                                                                                           1,1           Top

