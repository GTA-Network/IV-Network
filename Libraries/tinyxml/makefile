CC=g++
CFLAGS=-m32 -c -Wall -D_SERVER -static
LDFLAGS=-lpthread -static
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=libtinyxml.a

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	ar -rv $@ $(OBJECTS) 

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -Rf *.o $(EXECUTABLE)
