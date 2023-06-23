#pragma once
#ifndef _PXEM_H
#define _PXEM_H

#include "constants.h"

typedef int PxemData;

/**
 * data type for Pxem's program source.
 */
struct Source {
	PxemData *name;
	size_t name_length;
	PxemData content[CONTENT_MAX_SIZE];
	size_t content_length;
};
typedef struct Source Source;

/**
 * data type to define Pxem's working storage.
 */
struct Process {
	size_t pc; /* program counter. src->name[pc] */
	Source *src;

	size_t sp; /* stack pointer. stack[sp] */
	PxemData stack[STACK_MAX_SIZE];

	int has_heap_data;
	PxemData heap;
};
typedef struct Process Process;

/**
 * why not manage with these global variables?
 */
extern Source globalSource; /* Since program shall not modify itself, why not store here */

extern Process globalProcesses[PROCESS_MAX_SIZE + 1];
extern size_t globalProcessingAt; /**
				* shall be 1 <= globalProcessingAt < PROCESS_MAX_SIZE
				* while running; 0 when halt
				*/

/**
 * functions
 */

/**
 * @function pxem_init
 * @arg
 */
void pxem_init(Source *);
void pxem_run(void);
void pxem_step(void);
#endif /* _PXEM_H */
