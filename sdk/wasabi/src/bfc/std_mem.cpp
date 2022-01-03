#include "precomp.h"

#include "std_mem.h"

#include "std_math.h"
#include "assert.h"

#define USE_MALLOC
//#define COUNTUSAGE

#ifdef WIN32
#ifdef USE_MALLOC
#include <malloc.h>
#endif
#endif

#ifdef USE_MEM_CHECK
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#ifdef COUNTUSAGE
static totalMem=0;
#endif

#define USER_PTR_TO_ALLOCMGR_PTR(x) (((char *)x)-4)
//CUT #define ALLOCMGR_PTR_TO_USER_PTR(x) (((char *)x)+4)
static inline void *ALLOCMGR_PTR_TO_USER_PTR(void *x) {
  if (x == 0) return x;	// don't hide NULL bitch
  return ((char *)x + 4);
}
#define ALLOCMGR_SIZE(x) *((int *)x)

void *DO_MALLOC(int size EXTRA_INFO) {
  ASSERT(size > 0);
  if (size <= 0) return NULL;

#ifdef COUNTUSAGE
  totalMem+=size;
#endif

#ifndef USE_MEM_CHECK
 #ifndef USE_MALLOC
  void *p = GlobalAlloc(GPTR, size+4);
 #else
  void *p = malloc(size+4);
  if (p != NULL) MEMSET(p, 0, size+4);//BU added in response to talkback info
 #endif
#else
 #ifndef USE_MALLOC
  void *p = GlobalAlloc(GPTR, size+4, file, line);
 #else
  void *p = _malloc_dbg(size+4, _NORMAL_BLOCK, file, line);
  if (p != NULL) memset(p, 0, size+4);
 #endif
#endif
 if (p) ALLOCMGR_SIZE(p) = size;
 return ALLOCMGR_PTR_TO_USER_PTR(p);
}

void *DO_CALLOC(int records, int recordsize EXTRA_INFO) {
  ASSERT(records > 0 && recordsize > 0);
  return DO_MALLOC(records * recordsize EXTRA_PARAMS);
}

void DO_FREE(void *ptr EXTRA_INFO) {
  if (ptr == NULL) return;

#ifdef COUNTUSAGE
 totalMem -= ALLOCMGR_SIZE(USER_PTR_TO_ALLOCMGR_PTR(ptr));
#endif

#ifndef USE_MEM_CHECK
 #ifndef USE_MALLOC
  GlobalFree(USER_PTR_TO_ALLOCMGR_PTR(ptr));
 #else
  free(USER_PTR_TO_ALLOCMGR_PTR(ptr));
 #endif
#else
 #ifndef USE_MALLOC
  GlobalFree(USER_PTR_TO_ALLOCMGR_PTR(ptr), file, line); // FG> same as GlobalAlloc here, i'd like a way to translate my define inside the macro
 #else
  _free_dbg(USER_PTR_TO_ALLOCMGR_PTR(ptr), _NORMAL_BLOCK);
 #endif
#endif
}

// Note: MEMCPY allows dest and src to overlap
void MEMCPY(void *dest, const void *src, int n) {
  ASSERT(dest != NULL);
  ASSERT(src != NULL);
  ASSERT(n >= 0);
  memmove(dest, src, n);
}

void *DO_MEMDUP(const void *src, int n EXTRA_INFO) {
  void *ret;
  ASSERT(n >= 0);
  if (src == NULL || n == 0) return NULL;
  ret = DO_MALLOC(n EXTRA_PARAMS);
  if (ret == NULL) return NULL;
  MEMCPY(ret, src, n);
  return ret;
}

#define FAKE_REALLOC

//PORTME: BU> umm... tried to merge w/ linux ver but doesn't look right
void *DO_REALLOC(void *ptr, int size EXTRA_INFO) {
  ASSERT(size >= 0);

  if (size == 0) {
#ifdef USE_MEM_CHECK
    DO_FREE(ptr, file, line);
#else
    DO_FREE(ptr);
#endif
    return NULL;
  }

#ifdef USE_MEM_CHECK
  if(ptr == NULL) return DO_MALLOC(size, file, line);
#else
  if(ptr == NULL) return DO_MALLOC(size);
#endif
  void *r = NULL;

  int oldsize = ALLOCMGR_SIZE(USER_PTR_TO_ALLOCMGR_PTR(ptr));

#ifdef COUNTUSAGE
 #ifndef USE_MALLOC
 totalMem -= oldsize;
 #endif
#endif

#ifndef USE_MEM_CHECK
 #ifndef USE_MALLOC
  r = GlobalReAlloc((HGLOBAL)USER_PTR_TO_ALLOCMGR_PTR(ptr), size+4, GMEM_ZEROINIT);
 #else
  r = realloc(USER_PTR_TO_ALLOCMGR_PTR(ptr), size+4);

 #endif // use_malloc
#else // mem_spy
 #ifndef USE_MALLOC
  r = GlobalReAlloc((HGLOBAL)USER_PTR_TO_ALLOCMGR_PTR(ptr), size+4, file, line);
 #else
  r = _realloc_dbg(USER_PTR_TO_ALLOCMGR_PTR(ptr), size+4, _NORMAL_BLOCK, file, line);
 #endif
#endif

 // r is an ALLOCMGR pointer

  if (r != NULL) {
    ALLOCMGR_SIZE(r) = size;
    r = ALLOCMGR_PTR_TO_USER_PTR(r);
  } else {
    // realloc failed !
    void *newblock = MALLOC(size);
    MEMCPY(newblock, ptr, MIN(oldsize, size));
    FREE(ptr);
    r = newblock;
  }

 // r is now a USER pointer

#ifdef COUNTUSAGE
  totalMem += size;
#endif

  #ifdef USE_MALLOC
   if (size > oldsize)
    MEMZERO((char *)r+oldsize, size-oldsize);
  #endif

  return r;
}

int MEMSIZE(void *ptr) {
  return ALLOCMGR_SIZE(USER_PTR_TO_ALLOCMGR_PTR(ptr));
}
