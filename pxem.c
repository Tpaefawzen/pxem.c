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

/**
 * initializer; randomizer.
 */
void pxem_init(void){
	srandom((unsigned int)time(NULL));
}


