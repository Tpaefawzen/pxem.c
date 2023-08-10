#pragma once

/**
 * @file pxem.h
 * @description
 * Pxem's data types and pxem processing functions.
 * Data types are prefixed with `Pxem`.
 * Functions are prefixed with `pxem_`.
 */

#ifndef _PXEM_H
#define _PXEM_H

#include <stdint.h>
#include <stdbool.h>

#include "constants.h"

/**
 * @type PxemInt
 * @description
 * Signed integer who repsesents internal data.
 */
typedef int64_t PxemInt;

/**
 * @struct PxemProcess
 * @description
 * Root process.
 */
struct PxemProcess {
	/**
	 * @property vm_stack
	 * @description
	 * Virtual machines.
	 */
	struct PxemVmStack vm_stack;

	/**
	 * @property filename
	 * @description
	 * Null-termined?
	 */
	PxemInt *filename;
	PxemInt *content;
	bool has_read_content;
};
typedef struct PxemProcess PxemProcess;

/**
 * @struct PxemVmStack
 * @descrption
 * Stack for @struct PxemVm; it stacks Pxem's virtual machines.
 */
struct PxemVmStack {
	/**
	 * @property top
	 * @description Points to stack's top.
	 */
	struct PxemVm *top;
};
typedef struct PxemVmStack PxemVmStack;


/**
 * data type for Pxem's program source.
 */
struct Source {
	PxemInt *name;
	size_t name_length;
	PxemInt content[CONTENT_MAX_SIZE];
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
	PxemInt stack[STACK_MAX_SIZE];

	int has_heap_data;
	PxemInt heap;
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
