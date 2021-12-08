CC=g++
IDIR=.
CPPFLAGS=-Wall -std=c++2a -I$(IDIR)
OBJ = main.o

%.o: %.cpp
	$(CC) -c -o $@ $< $(CPPFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CPPFLAGS)

clean:
	rm -rf *.o
