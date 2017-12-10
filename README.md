# Sorting Numbers

An external sort implementation for 32-bit integers. Read about it [here](https://nicluo.com/blog/sorting-a-billion-numbers/).

## Requirements

Requires the GNU split program. On Mac OS X, installing the Homebrew package `coreutils` satisfies the dependency.

A makefile is included with this. run `make` to build and `make clean` to remove all build artifacts.

## Generating input

A random number generator is included with this. To generate a billion numbers (around 9.8GB)

    ./generate -n 1000000000 -o input.txt

Or in parallel

    ./generate -n 250000000 -o input-1.txt &
    ./generate -n 250000000 -o input-2.txt &
    ./generate -n 250000000 -o input-3.txt &
    ./generate -n 250000000 -o input-4.txt &
    wait
    cat input-*.txt >> input.txt
    rm input-*.txt

## Running the sort

The included shell script `sort.sh` sorts the input list at `input.txt` to `output.txt`.

    chmod a+x sort.sh
    ./sort.sh

## What does sort.sh do

The sorting method used splits the input file into 12 parts. The GNU `split` program is used for this.

On Mac OS X with `coreutils` installed, the `split` program is aliased as `gsplit` instead.

A simple quick sort implementation sorts all individual files. The code is in `sort.cpp`.

A 12-way merge is used on the sorted sub lists to build the final output file. The code is in `merge.cpp`.
