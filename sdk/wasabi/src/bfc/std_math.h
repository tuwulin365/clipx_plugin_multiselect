#ifndef _STD_MATH_H
#define _STD_MATH_H

#include <bfc/std.h>

// FG> doesn't work for me without this include (error C2039: 'sin' : is not a member of '`global namespace'')
#ifdef __cplusplus
#include <math.h>
static inline double SIN(double a) { return ::sin(a); }
static inline double COS(double a) { return ::cos(a); }
static inline double SQRT(double a) { return ::sqrt(a); }

static inline unsigned long BSWAP(unsigned long input) {
#if defined(_MSC_VER) && !defined(_WIN64) 
  _asm {
    mov eax, input
    bswap eax
    mov input, eax
  };
  return input;
#else
#  if defined(GCC) && !defined(DARWIN)
  __asm__ volatile (
		    "\tmov %0, %%eax\n"
		    "\tbswap %%eax\n"
		    : "=m" (input)
		    : 
		    : "%eax" );
#  else
  unsigned char ret[4];
  unsigned char *s = reinterpret_cast<unsigned char *>(&input);
  ret[0] = s[3];
  ret[1] = s[2];
  ret[2] = s[1];
  ret[3] = s[0];
  return *reinterpret_cast<unsigned long *>(ret);
#  endif
#endif
}
#else
#define SIN(a) sin(a)
#define COS(a) sin(a)
#define SQRT(a) sqrt(a)
unsigned long BSWAP_C(unsigned long input);
#define BSWAP BSWAP_C
#endif

#ifdef __cplusplus

#ifdef MIN
#undef MIN
#endif

#ifdef MAX
#undef MAX
#endif

// neat trick from C++ book, p. 161
template<class T> inline T MAX(T a, T b) { return a > b ? a : b; }
template<class T> inline T MIN(T a, T b) { return a > b ? b : a; }
template<class T> inline T MINMAX(T a, T minval, T maxval) {
  return (a < minval) ? minval : ( (a > maxval) ? maxval : a );
}


#ifdef ABS
#undef ABS
#endif

#ifdef SQR
#undef SQR
#endif

#ifdef CMP3
#undef CMP3
#endif

#ifdef SIGN
#undef SIGN
#endif

// and a couple of my own neat tricks :) BU
template<class T> inline T ABS(T a) { return a < 0 ? -a : a; }
template<class T> inline T SQR(T a) { return a * a; }
template<class T> inline int CMP3(T a, T b) {
  if (a < b) return -1;
  if (a == b) return 0;
  return 1;
}
template<class T> inline T SIGN(T a) {
  return (a < 0) ? -T(1) : ( (a == 0) ? T(0) : T(1) );
}

static inline RGB24 RGBTOBGR(RGB24 col) {
  return ((col & 0xFF00FF00) | ((col & 0xFF0000) >> 16) | ((col & 0xFF) << 16));
}
static inline RGB24 BGRTORGB(RGB24 col) { return RGBTOBGR(col); }
static inline ARGB32 BGRATOARGB(ARGB32 col) { return RGBTOBGR(col); }

void premultiplyARGB32(ARGB32 *words, int nwords=1);

namespace StdMath {
  int mulDiv(int m1, int m2, int d);
};

#ifdef WIN32
#include <float.h>
#endif
#define STDMATH_FLOAT_MAX FLT_MAX

#else // not __cplusplus
void premultiplyARGB32(ARGB32 *words, int nwords);
#endif

#endif
