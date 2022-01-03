#ifndef _STD_MEM_H
#define _STD_MEM_H

#include "platform/platform.h"

//#define USE_MEM_CHECK

#ifdef USE_MEM_CHECK
#define EXTRA_INFO                , char *file, int line
#define EXTRA_PARAMS              , file, line
#define EXTRA_INFO_HERE                , __FILE__, __LINE__
#define MALLOC(size)                DO_MALLOC(size, __FILE__, __LINE__)
#define CALLOC(records, recordsize) DO_CALLOC(records, recordsize, __FILE__, __LINE__)
#define REALLOC(ptr, size)          DO_REALLOC(ptr, size, __FILE__, __LINE__)
#define FREE(ptr)                   DO_FREE(ptr, __FILE__, __LINE__)
#define MEMDUP(src, n)              DO_MEMDUP(src, n, __FILE__, __LINE__)
#define STRDUP(ptr)                 DO_STRDUP(ptr, __FILE__, __LINE__)
#define WSTRDUP(ptr)                DO_WSTRDUP(ptr, __FILE__, __LINE__)
#else
#define EXTRA_INFO
#define EXTRA_PARAMS
#define EXTRA_INFO_HERE
#define MALLOC(size)                DO_MALLOC(size)
#define CALLOC(records, recordsize) DO_CALLOC(records, recordsize)
#define REALLOC(ptr, size)          DO_REALLOC(ptr, size)
#define FREE(ptr)                   DO_FREE(ptr)
#define MEMDUP(src, n)              DO_MEMDUP(src, n)
#define STRDUP(ptr)                 DO_STRDUP(ptr)
#define WSTRDUP(ptr)                DO_WSTRDUP(ptr)
#endif

void *DO_MALLOC(int size EXTRA_INFO);
void *DO_CALLOC(int records, int recordsize EXTRA_INFO);
void *DO_REALLOC(void *ptr, int size EXTRA_INFO);
void DO_FREE(void *ptr EXTRA_INFO);

void *DO_MEMDUP(const void *src, int n EXTRA_INFO);
void MEMCPY(void *dest, const void *src, int n);

int MEMSIZE(void *ptr);

#ifdef __cplusplus
static __inline int MEMCMP(const void *buf1, const void *buf2, int count) {
  return memcmp(buf1, buf2, count);
}
static __inline void MEMSET(void *dest, int c, int n) {
  memset(dest, c, n);
}
static __inline void MEMZERO(void *dest, int nbytes) {
  memset(dest, 0, nbytes);
}
#else
#define MEMCMP memcmp
#define MEMSET memset
#define MEMZERO(dest, nbytes) memset(dest, 0, nbytes)
#endif

#ifdef __cplusplus

// these are for structs and basic classes only
static __inline void ZERO(int &obj) { obj = 0; }
template<class T>
inline void ZERO(T &obj) { MEMZERO(&obj, sizeof(T)); }

// generic version that should work for all types
template<class T>
inline void MEMFILL(T *ptr, T val, unsigned int n) {
  for (int i = 0; i < n; i++) ptr[i] = val;
}

// asm 32-bits version
void MEMFILL32(void *ptr, unsigned long val, unsigned int n);

// helpers that call the asm version
template<>
inline void MEMFILL<unsigned long>(unsigned long *ptr, unsigned long val, unsigned int n) { MEMFILL32(ptr, val, n); }

template<>
void MEMFILL<unsigned short>(unsigned short *ptr, unsigned short val, unsigned int n);

// int
template<>
inline void MEMFILL<int>(int *ptr, int val, unsigned int n) {
  MEMFILL32(ptr, *reinterpret_cast<unsigned long *>(&val), n);
}

// float
template<>
inline void MEMFILL<float>(float *ptr, float val, unsigned int n) {
  MEMFILL32(ptr, *reinterpret_cast<unsigned long *>(&val), n);
}

#endif	// __cplusplus defined

#endif
