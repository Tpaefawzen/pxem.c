#pragma once

#include "constants.h"

/* data type for Pxem's program source. */
struct Source {
	int *name;
	size_t name_length;
	int content[CONTENT_MAX_SIZE];
	size_t content_length;
};
typedef struct Source Source;

void pxem_init(void);
