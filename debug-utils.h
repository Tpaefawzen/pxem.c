#pragma once
#ifndef _DEBUG_UTILS_H
#define _DEBUG_UTILS_H

#if defined(NDEBUG)
#define DPRINTF(...) /* nop */
#else
#define DPRINTF(...) fprintf(stderr, __VA_ARGS__)
#endif
#endif /* _DEBUG_UTILS_H */
