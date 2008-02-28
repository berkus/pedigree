/*
 * Copyright (c) 2008 James Molloy, James Pritchett, Jörg Pfähler, Matthew Iselin
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef KERNEL_UTILITY_H
#define KERNEL_UTILITY_H

#include <stdarg.h>
#include <processor/types.h>

#ifdef __cplusplus
extern "C" {
#endif

int vsprintf(char *buf, const char *fmt, va_list arg);
int sprintf(char *buf, const char *fmt, ...);
int strlen(const char *buf);
int strcpy(char *dest, const char *src);
int strncpy(char *dest, const char *src, int len);
int memset(void *buf, int c, size_t len);
void memcpy(void *dest, const void *src, size_t len);

int strcmp(const char *p1, const char *p2);
int strncmp(const char *p1, const char *p2, int n);
char *strcat(char *dest, const char *src);
char *strncat(char *dest, const char *src, int n);

char *strchr(const char *str, char target);
char *strrchr(const char *str, char target);

unsigned long strtoul(const char *nptr, char **endptr, int base);

#ifdef __cplusplus
}
#endif

#define MAX_FUNCTION_NAME 128
#define MAX_PARAMS 32
#define MAX_PARAM_LENGTH 64

typedef struct
{
  char name[128]; // Function name.
  char params[32][64]; // Parameters.
  int nParams;
} symbol_t;

void demangle(const char *src, symbol_t *sym);

#endif
