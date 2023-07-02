#ifndef _KSTRING_H
#define _KSTRING_H

#include "kdef.h"

void *memset(void *s, int c, size_t n);
void *memcpy(void *dest, const void *src, size_t n);
long unsigned int strlen(const char *str);
char *strcpy(char *dest, const char *src);

#endif /* _KSTRING_H */