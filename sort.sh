#!/usr/bin/env bash

# Split file into 12 chunks, keeping individual lines together
gsplit -n l/12 -d input.txt output-

# Sort 12 individual chunks in parallel
{
	./sort -f output-00
	./sort -f output-01
	./sort -f output-02
} &
{
	./sort -f output-03
	./sort -f output-04
	./sort -f output-05
} &
{
	./sort -f output-06
	./sort -f output-07
	./sort -f output-08
} &
{
	./sort -f output-09
	./sort -f output-10
	./sort -f output-11
} &
wait

# 12-way merge of all the individual chunks
./merge -o output.txt -f output-*

# Remove chunks
rm output-*

