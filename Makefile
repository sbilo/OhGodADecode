CC=gcc
CFLAGS+=-O3 -Wall --std=c99

ohgodaencode: ohgodaencode.c
	$(CC) $(CFLAGS) -o $@ $^ -lconfig

clean:
	rm -f ohgodanecode
