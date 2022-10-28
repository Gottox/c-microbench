/**
 * @author      : Enno Boland (mail@eboland.de)
 * @file        : memcpy
 * @created     : Friday Oct 28, 2022 08:49:42 CEST
 */

#include "../src/exec_time.h"
#include "../src/test_data.h"
#include <stdlib.h>
#include <string.h>

#define REPETITIONS 1000000

int
main(int argc, char *argv[]) {
	char **buffers = malloc(sizeof(char *) * REPETITIONS);
	if (buffers == NULL) {
		return 1;
	}

	for (int i = 0; i < REPETITIONS; i++) {
		buffers[i] = malloc(sizeof(char) * TEST_DATA_SIZE);
		if (buffers[i] == NULL) {
			return 1;
		}
	}

	timer_start();
	for (int i = 0; i < REPETITIONS; i++) {
		memcpy(buffers[i], microbench_test_data, TEST_DATA_SIZE);
	}
	timer_end();
}
