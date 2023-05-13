#pragma once

enum {
	STACK_MAX_SIZE = 4096,
};

struct Source {
	char* name;
	char* content;
	size_t content_length;
};

typedef struct Source Source;
