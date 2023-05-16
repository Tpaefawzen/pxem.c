#pragma once

#if defined(NDEBUG)
#define DPRINTF(...) /* nop */
#else
#define DPRINTF(...) fprintf(stderr, __VA_ARGS__)
#endif
