#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "debug-utils.h"

char* myName;

int main(int, char**);
void usage(void);

int
main(int argc, char** argv){
	// what is this program name?
	myName = argv[0];

	// variables
	Source src = {0};

	// this program's usage is very simple so like this
	if ( argc != 2 ){
		usage();
		/* noreturn */
	}
	
	// assuming file path delimiter is '/', obtain basename
	{
		const int pathDelimiter = '/';

		char* fname = argv[1];
		char* maybeBasename = strrchr(fname, pathDelimiter);

		src.name = fname;
		if ( maybeBasename ) {
			src.name = ++maybeBasename;
		}

		DPRINTF("%s:%d: Filename: %s\n", __FILE__, __LINE__, src.name);
	}

	// let's obtain content
	{
		// help what should i do
	}

	// finally
	exit(EXIT_SUCCESS);
}

void
usage(void){
	fprintf(stderr, "Usage: %s FILE\n", myName);
	exit(EXIT_FAILURE);
}
