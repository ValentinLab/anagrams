CFLAGS = -Wall -g -std=c99

TARGETS = anagrammes-query

all: $(TARGETS)

anagrammes-query: anagrammes.o anagrammes-query.o

clean:
	rm -f *.o

mrproper: clean
	rm $(TARGETS)
