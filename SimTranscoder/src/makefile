CFLAGS = -Wall -g

# Should be equivalent to your list of C files, if you don't build selectively
SRC=$(wildcard *.c)
HEADERS=$(wildcard *.h)

transcoder: $(HEADERS) $(SRC)
	gcc -o $@ $^ $(CFLAGS)
