
#include "utils/streams.hpp"
#include <stdint.h>
#include <stdarg.h>

namespace cooboc {

static char *long_to_string_with_divisor(char *p,
                                         long num,
                                         unsigned radix,
                                         long divisor);
static char *ftoa(char *p, double num, unsigned long precision);

uint32_t sprintf(char *dest, const char * const fmt, ...) {
	va_list ap;
  int formatted_bytes;

  va_start(ap, fmt);
  formatted_bytes = vsprintf(dest, fmt, ap);
  va_end(ap);
	dest[formatted_bytes] = '\0';
  return formatted_bytes;
}


static char NULL_STR[] {"(null)"};
#define MAX_FILLER 12
#define FLOAT_PRECISION 9
uint32_t vsprintf(char *dest, const char *fmt, va_list ap) {
  char *p, *s, c, filler;
  float f;
	int i, precision, width;
	int n = 0;
  bool is_long, left_align;
  long l;
	char tmpbuf[MAX_FILLER*2];

  while (true) {
    c = *fmt++;
    if (c == 0)
      return n;
    if (c != '%') {
			dest[n] = c;
      n++;
      continue;
    }
    p = tmpbuf;
    s = tmpbuf;
    left_align = false;
    if (*fmt == '-') {
      fmt++;
      left_align = true;
    }
    filler = ' ';
    if (*fmt == '0') {
      fmt++;
      filler = '0';
    }
    width = 0;
    while (true) {
      c = *fmt++;
      if (c >= '0' && c <= '9')
        c -= '0';
      else if (c == '*')
        c = va_arg(ap, int);
      else
        break;
      width = width * 10 + c;
    }
    precision = 0;
    if (c == '.') {
      while (true) {
        c = *fmt++;
        if (c >= '0' && c <= '9')
          c -= '0';
        else if (c == '*')
          c = va_arg(ap, int);
        else
          break;
        precision *= 10;
        precision += c;
      }
    }
    /* Long modifier.*/
    if (c == 'l' || c == 'L') {
      is_long = true;
      if (*fmt)
        c = *fmt++;
    }
    else
      is_long = (c >= 'A') && (c <= 'Z');

    /* Command decoding.*/
    switch (c) {
    case 'c':
      filler = ' ';
      *p++ = va_arg(ap, int);
      break;
    case 's':
      filler = ' ';
      if ((s = va_arg(ap, char *)) == 0)
        s = NULL_STR;
      if (precision == 0)
        precision = 32767;
      for (p = s; *p && (--precision >= 0); p++)
        ;
      break;
    case 'D':
    case 'd':
    case 'I':
    case 'i':
      if (is_long)
        l = va_arg(ap, long);
      else
        l = va_arg(ap, int);
      if (l < 0) {
        *p++ = '-';
        l = -l;
      }
      p = long_to_string_with_divisor(p, l, 10, 0);
      break;
    case 'f':
      f = (float) va_arg(ap, double);
      if (f < 0) {
        *p++ = '-';
        f = -f;
      }
      p = ftoa(p, f, precision);
      break;
    case 'X':
    case 'x':
      c = 16;
      goto unsigned_common;
    case 'U':
    case 'u':
      c = 10;
      goto unsigned_common;
    case 'O':
    case 'o':
      c = 8;
unsigned_common:
      if (is_long)
        l = va_arg(ap, unsigned long);
      else
        l = va_arg(ap, unsigned int);
      p = long_to_string_with_divisor(p, l, c, 0);
      break;
    default:
      *p++ = c;
      break;
    }
    i = (int)(p - s);
    if ((width -= i) < 0)
      width = 0;
    if (left_align == false)
      width = -width;
    if (width < 0) {
      if (*s == '-' && filler == '0') {
				dest[n] = (uint8_t)*s++;
        n++;
        i--;
      }
      do {
				dest[n] = (uint8_t)filler;
        n++;
      } while (++width != 0);
    }
    while (--i >= 0) {
			dest[n] = (uint8_t)*s++;
      n++;
    }

    while (width) {
			dest[n] = (uint8_t)filler;
      n++;
      width--;
    }
  }
}



static char *long_to_string_with_divisor(char *p,
                                         long num,
                                         unsigned radix,
                                         long divisor) {
  int i;
  char *q;
  long l, ll;

  l = num;
  if (divisor == 0) {
    ll = num;
  } else {
    ll = divisor;
  }

  q = p + MAX_FILLER;
  do {
    i = (int)(l % radix);
    i += '0';
    if (i > '9')
      i += 'A' - '0' - 10;
    *--q = i;
    l /= radix;
  } while ((ll /= radix) != 0);

  i = (int)(p + MAX_FILLER - q);
  do
    *p++ = *q++;
  while (--i);

  return p;
}


static const long pow10[FLOAT_PRECISION] = {
    10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000
};

static char *ftoa(char *p, double num, unsigned long precision) {
  long l;

  if ((precision == 0) || (precision > FLOAT_PRECISION))
    precision = FLOAT_PRECISION;
  precision = pow10[precision - 1];

  l = (long)num;
  p = long_to_string_with_divisor(p, l, 10, 0);
  *p++ = '.';
  l = (long)((num - l) * precision);
  return long_to_string_with_divisor(p, l, 10, precision / 10);
}



}

/*
int chprintf(BaseSequentialStream *chp, const char *fmt, ...) {
  va_list ap;
  int formatted_bytes;

  va_start(ap, fmt);
  formatted_bytes = chvprintf(chp, fmt, ap);
  va_end(ap);

  return formatted_bytes;
}
*/