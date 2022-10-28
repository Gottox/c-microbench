######################################################################
# @author      : Enno Boland (mail@eboland.de)
# @file        : Makefile
# @created     : Friday Oct 28, 2022 08:56:15 CEST
######################################################################

CC=gcc

OBJ = \
	src/exec_time.o \
	src/test_data.o \

LIBS = -lzstd -lzlib

all: bin/memcpy bin/zstd bin/gzip
	bin/memcpy
	bin/zstd
	bin/gzip

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

bin/%: bin/%.c $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f src/*.o bin/memcpy bin/zstd bin/gzip

