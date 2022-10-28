/**
 * @author      : Enno Boland (mail@eboland.de)
 * @file        : memcpy
 * @created     : Friday Oct 28, 2022 08:49:42 CEST
 */

#include "../src/exec_time.h"
#include "../src/test_data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

#define REPETITIONS 1000000

int
main(int argc, char *argv[]) {
	int rv = 0;
	unsigned char **buffers = malloc(sizeof(char *) * REPETITIONS);
	unsigned char *compressed;
	unsigned long compressed_size = 0;
	unsigned long uncompressed_size = 0;
	if (buffers == NULL) {
		fputs("malloc failed\n", stderr);
		return 1;
	}

	compressed = malloc(sizeof(char) * TEST_DATA_SIZE * 2);
	if (compressed == NULL) {
		fputs("malloc failed\n", stderr);
		return 1;
	}
	compressed_size = TEST_DATA_SIZE * 2;
	rv = compress(compressed, &compressed_size,
				  (const unsigned char *)microbench_test_data, TEST_DATA_SIZE);
	if (rv != Z_OK) {
		fputs("compress() failed.\n", stderr);
		return 1;
	}

	for (int i = 0; i < REPETITIONS; i++) {
		buffers[i] = malloc(sizeof(char) * TEST_DATA_SIZE);
		if (buffers[i] == NULL) {
			fputs("malloc failed\n", stderr);
			return 1;
		}
	}

	timer_start();
	for (int i = 0; i < REPETITIONS; i++) {
		uncompressed_size = TEST_DATA_SIZE;
		rv = uncompress(buffers[i], &uncompressed_size, compressed,
						compressed_size);
		if (rv != Z_OK) {
			fputs("ZSTD_decompress() failed.\n", stderr);
			return 1;
		}
	}
	timer_end();
}
