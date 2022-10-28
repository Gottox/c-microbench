/**
 * @author      : Enno Boland (mail@eboland.de)
 * @file        : exec_time
 * @created     : Friday Oct 28, 2022 08:35:21 CEST
 */

#include "exec_time.h"
#include <stdio.h>

static struct timeval tv_start;

int
timer_start() {
	fputs("Starting timer\n", stderr);
	gettimeofday(&tv_start, 0);

	return 0;
}

int
timer_end() {
	struct timeval tv_end;

	gettimeofday(&tv_end, 0);
	long s = tv_end.tv_sec - tv_start.tv_sec;
	long us = tv_end.tv_usec - tv_start.tv_usec;
	if (us < 0) {
		us += 1000000;
		s -= 1;
	}

	fprintf(stderr, "Execution time: %ld.%06ld\n", s, us);

	return 0;
}
