#ifndef BASE_H
#define BASE_H

#include <locale.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define HEIGHT  66
#define WIDTH  198

#define W1_NLINES  24
#define W1_NCOLS   80

#define W2_NLINES  34
#define W2_NCOLS   20

#define W3_NLINES  10
#define W3_NCOLS   80

#define NLINES  (W1_NLINES + W3_NLINES)
#define NCOLS   (W1_NCOLS + W2_NCOLS)

#define MIN(a, b) (((a)<(b)) ? (a) : (b))
#define MAX(a, b) (((a)>(b)) ? (a) : (b))

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

typedef int8_t i8;
typedef int16_t i16;

#endif
