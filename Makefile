CC=gcc
CFLAGS=-O3 -Wall --std=c99

ohgodadecode: ohgodadecode.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f ohgodadecode
