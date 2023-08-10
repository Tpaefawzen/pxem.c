/**
 * NOTE.
 * Requiring POSIX's srandom() and random() from stdlib.h; not from ISO C
 */

// I want to use random() and srandom() from stdlib.h from POSIX
#define _XOPEN_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "pxem.h"

Source globalSource = {0};
Process globalProcesses[PROCESS_MAX_SIZE + 1] = {0};
size_t globalProcessingAt = 1;

/**
 * initializer; randomizer.
 */
void pxem_init(Source *src){
	srandom((unsigned int)time(NULL));

	globalSource = *src;

#if 0
	size_t globalProcessingAt = 1; /* indicates beginning */
	Process rootP = globalProcesses[globalProcessingAt];
	globalProcesses[globalProcessingAt] = (struct Process) {
		.pc = 0,
		.src = src,
		
		.sp = 0,
		
	       	.has_heap_data = 0,
	};
#endif
}

/**
 * runner
 */
void pxem_run(void){
	// TODO
}
