CC=g++
CFLAGS=-O3

.PHONY: clean default

default: generate sort merge

generate: generate.cpp
	$(CC) $(CFLAGS) -o generate generate.cpp

sort: sort.cpp
	$(CC) $(CFLAGS) -o sort sort.cpp

merge: merge.cpp
	$(CC) $(CFLAGS) -o merge merge.cpp

clean:
	rm generate merge sort
