#ifndef GLOB_H
#define GLOB_H

#include <sys/types.h>

typedef struct
{
  size_t gl_pathc;
  char **gl_pathv;
  size_t gl_offs;
} glob_t;

#define GLOB_APPEND 1
#define GLOB_DOOFFS 2
#define GLOB_ERR    3
#define GLOB_MARK   4
#define GLOB_NOCHECK 5
#define GLOB_NOESCAPE 6
#define GLOB_NOSORT 7

#define GLOB_ABORTED 1
#define GLOB_NOMATCH 2
#define GLOB_NOSPACE 3
#define GLOB_NOSYS 4

int glob(const char *, int, int (*)(const char *, int), glob_t*);
void globfree(glob_t *);

#endif
