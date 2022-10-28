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
#include <zstd.h>

#define REPETITIONS 1000000

int
main(int argc, char *argv[]) {
	int rv = 0;
	char **buffers = malloc(sizeof(char *) * REPETITIONS);
	char *compressed;
	int compressed_size = 0;
	if (buffers == NULL) {
		fputs("malloc failed\n", stderr);
		return 1;
	}

	compressed = malloc(sizeof(char) * TEST_DATA_SIZE * 2);
	if (compressed == NULL) {
		fputs("malloc failed\n", stderr);
		return 1;
	}
	rv = ZSTD_compress(compressed, TEST_DATA_SIZE * 2, microbench_test_data,
					   TEST_DATA_SIZE, 1);
	if (ZSTD_isError(rv)) {
		fputs("ZSTD_compress() failed.\n", stderr);
		fputs(ZSTD_getErrorName(rv), stderr);
		fputs("\n", stderr);
		return 1;
	}
	compressed_size = rv;

	for (int i = 0; i < REPETITIONS; i++) {
		buffers[i] = malloc(sizeof(char) * TEST_DATA_SIZE);
		if (buffers[i] == NULL) {
			fputs("malloc failed\n", stderr);
			return 1;
		}
	}

	timer_start();
	for (int i = 0; i < REPETITIONS; i++) {
		rv = ZSTD_decompress(buffers[i], TEST_DATA_SIZE, compressed,
							 compressed_size);
		if (ZSTD_isError(rv)) {
			fputs("ZSTD_decompress() failed.\n", stderr);
			fputs(ZSTD_getErrorName(rv), stderr);
			fputs("\n", stderr);
			return 1;
		}
	}
	timer_end();
}
