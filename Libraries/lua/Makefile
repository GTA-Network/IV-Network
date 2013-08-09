SOURCES+=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)

all: $(SOURCES)
	gcc -m32 -c -Wall -O2 $(SOURCES)
clean:
	rm -Rf $(OBJECTS)