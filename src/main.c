#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "debug-utils.h"
#include "pxem.h"

char *myName;

enum {
	ENC_BYTE,
	ENC_UTF8,
	ENC_LOOSE_UTF8,
} _Encoding;
typedef enum _Encoding Encoding;

int fnameEncoding = ENC_BYTE;

void usage(void);
void fname2src(Source *src, char *fname);
void perrorWithFile(const char *);

int main(int, char **);

/**
 * @name perrorWithFile
 * @brief perror("%s: %s") where "%s: %s", myName, FILE
 * @global errno
 * @description
 * Error message shall be PROGRAM: FILE: MESSAGE.
 * You can edit FILE.
 */
void
perrorWithFile(const char *s){
	printf("%s: %s: %s\n", myName, s, strerror(errno));
}


/**
 * @name fname2src
 * @brief Null-terminated filename string to Pxem source.
 *
 * @param Source *src
 * To be Pxem source.
 *
 * @param char *fname
 * Null-terminated.
 *
 * @global fnameEncoding
 * Determines encoding for fname.
 *
 * @global errno
 * Stores when dynamic memory could not be allocated.
 */
void
fname2src(Source *src, char *fname){
	const size_t flen = strlen(fname);

	if ( !flen ){
		src->name_length = 0;
		return;
	}

	int *dst_program_source;
	if ( (dst_program_source = (int *)calloc(flen, sizeof(int))) == NULL ) {
		perror(myName);
		src->name_length = 0;
		return;
	}

	DPRINTF("%s:%s: dst_program_source: %p\n", __FILE__, __func__, dst_program_source);

	switch ( fnameEncoding ) {
	case ENC_BYTE:
		src->name = dst_program_source;
		src->name_length = flen;
		break;

	default:
		DPRINTF("%s:%s: FnameMode %d: unimplemented", __FILE__, __func__, fnameEncoding);
		assert(0);
	}
}

int
main(int argc, char **argv){
	// what is this program name?
	myName = argv[0];

	Source src = {0};

	// this program's usage is very simple so like this
	if ( argc != 2 ) {
		usage();
		/* noreturn */
	}
	
	char *basename;
	// assuming file path delimiter is '/', obtain basename
	{
		const int path_delimiter = '/';

		basename = argv[1]; /* null-term */
		char *maybe_basename = strrchr(basename, path_delimiter); /* null-term */

		if ( maybe_basename ) {
			basename = maybe_basename + 1;
		}

		DPRINTF("%s:%d: basename: %s\n", __FILE__, __LINE__, basename);

		fname2src(&src, basename);

		DPRINTF("%s:%d: src.name: %p\n", __FILE__, __LINE__, src.name);
		DPRINTF("%s:%d: src.name_length: %zu\n", __FILE__, __LINE__, src.name_length);

		if ( 0 ) {
		the_trap_0:
			DPRINTF("%s:%d: src.name: %p\n", __FILE__, __LINE__, src.name);
			DPRINTF("free(src.name);\n");
			free(src.name);
			src.name = NULL;

			goto finally;
		}

		DPRINTF("%s:%d: Filename: %s\n", __FILE__, __LINE__, (char *)src.name);
	}

	// let's obtain content
	{
		extern int errno;

		FILE *fp = fopen(argv[1], "rb");
		if ( fp == NULL || errno || ferror(fp) ) {
			perrorWithFile(basename);
			goto exit_content;
		}

		src.content_length = fread(src.content, sizeof(src.content) / sizeof(src.content[0]), sizeof(char), fp);

		int is_eof = feof(fp);
		int maybe_error = ferror(fp);
		DPRINTF("%s:%d: is_eof: %d maybe_error: %d\n", __FILE__, __LINE__, is_eof, maybe_error);

		if ( ! is_eof ) {
			fprintf(stderr, "%s: %s: file too long; truncated to %zu\n", myName, argv[1], sizeof(src.content)/sizeof(src.content[0]));
		}

		if ( maybe_error ) {
			perrorWithFile(basename);
		}

		clearerr(fp);

		fclose(fp);

		DPRINTF("%s:%d: src.content[0]: %d\n", __FILE__, __LINE__, src.content[0]);
		DPRINTF("%s:%d: src.content_length: %zu\n", __FILE__, __LINE__, src.content_length);
		goto exit_content;
	}
exit_content:

	// now I have prepared Pxem source, let's pass to interpreter.
	pxem_init(&src);
	pxem_run();

	goto the_trap_0;

finally:
	exit(EXIT_SUCCESS);
}

void
usage(void){
	fprintf(stderr, "Usage: %s FILE\n", myName);
	exit(EXIT_FAILURE);
}
