#ifndef KERNEL_UTILITY_H
#define KERNEL_UTILITY_H

#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

int vsprintf(char *buf, const char *fmt, va_list arg);
int sprintf(char *buf, const char *fmt, ...);
int strlen(const char *buf);
int strcpy(char *dest, const char *src);
int strncpy(char *dest, const char *src, int len);
int memset(unsigned char *buf, unsigned char c, unsigned int len);
void memcpy(unsigned char *dest, unsigned char *src, unsigned int len);

int strcmp(const char *p1, const char *p2);
int strncmp(const char *p1, const char *p2, int n);
char *strcat(char *dest, const char *src);
char *strncat(char *dest, const char *src, int n);

unsigned long strtoul(const char *nptr, char **endptr, int base);

#ifdef __cplusplus
}
#endif

#endif
