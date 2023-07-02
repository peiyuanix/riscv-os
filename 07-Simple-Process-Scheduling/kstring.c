#include "kstring.h"

void *memset(void *s, int c, size_t n)
{
  unsigned char *p = s;
  while (n--)
    *p++ = (unsigned char)c;
  return s;
}

void *memcpy(void *dest, const void *src, size_t n)
{
  unsigned char *d = dest;
  const unsigned char *s = src;
  while (n--)
    *d++ = *s++;
  return dest;
}

size_t strlen(const char *str)
{
  size_t length = 0;
  while (*str != '\0')
  {
    length++;
    str++;
  }
  return length;
}

char *strcpy(char *dest, const char *src)
{
  char *p = dest;
  while ((*p++ = *src++) != '\0')
    ;
  return dest;
}
