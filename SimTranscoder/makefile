CFLAGS = -Wall -lm -O3

# Should be equivalent to your list of C files, if you don't build selectively
SRC := $(wildcard src/*.c)
SRC_CIRCULAR=$(filter-out src/fila.heap.c, $(SRC))
SRC_HEAP=$(filter-out src/fila.circular.c, $(SRC))
HEADERS=$(wildcard *.h)

transcoder_heap: $(HEADERS) $(SRC_HEAP)
	gcc $^ $(CFLAGS) -o $@

transcoder_circular: $(HEADERS) $(SRC_CIRCULAR)
	gcc $^ $(CFLAGS) -o $@
