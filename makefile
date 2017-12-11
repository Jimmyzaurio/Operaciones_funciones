PROYECTO=operaciones_funcion
#DESTDIR=/usr/local/bin
CFLAGS=-std=c++0x
LDFLAGS=-lm -std=c++0x
CC=g++

all: $(PROYECTO)

%.o: %.cpp
	$(CC) -c $< $(CFLAGS)

$(PROYECTO): $(patsubst %.cpp,%.o,$(wildcard *.cpp))
	$(CC) $^ -o $@ $(LDFLAGS)

.PHONY: clean

uninstall:
	rm $(DESTDIR)/$(PROYECTO)

clean:
	 -rm -f *.o $(PROYECTO)
