#pragma once

#if defined(NDEBUG)
#define DPRINTF(...) /*nothing*/
#else
#define DPRINTF(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__)
#endif
