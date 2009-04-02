/*
 * Copyright (c) 2008 James Molloy, Jörg Pfähler, Matthew Iselin
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

#ifndef SYSCALL_NUMBERS_H
#define SYSCALL_NUMBERS_H

#define POSIX_OPEN        1
#define POSIX_WRITE       2
#define POSIX_READ        3
#define POSIX_CLOSE       4
#define POSIX_SBRK        5
#define POSIX_FORK        6
#define POSIX_EXECVE      7
#define POSIX_WAITPID     8
#define POSIX_EXIT        9
#define POSIX_OPENDIR    10
#define POSIX_READDIR    11
#define POSIX_REWINDDIR  12
#define POSIX_CLOSEDIR   13
#define POSIX_TCGETATTR  14
#define POSIX_TCSETATTR  15
#define POSIX_IOCTL      16
#define POSIX_STAT       17
#define POSIX_FSTAT      18
#define POSIX_GETPID     19
#define POSIX_CHDIR      20
#define POSIX_SELECT     21
#define POSIX_LSEEK      22

#define POSIX_SOCKET     23
#define POSIX_CONNECT    24
#define POSIX_SEND       25
#define POSIX_RECV       26
#define POSIX_BIND       27
#define POSIX_LISTEN     28
#define POSIX_ACCEPT     29
#define POSIX_RECVFROM   30
#define POSIX_SENDTO     31

#define POSIX_GETTIMEOFDAY 32
#define POSIX_DUP        33
#define POSIX_DUP2       34
#define POSIX_LSTAT      35
#define POSIX_UNLINK     36

#define POSIX_GETHOSTBYNAME   37
#define POSIX_GETHOSTBYADDR   38

#define POSIX_FCNTL      39
#define POSIX_PIPE       40

#define POSIX_MKDIR      41
#define POSIX_GETPWENT   42
#define POSIX_GETPWNAM   43
#define POSIX_GETUID     44
#define POSIX_GETGID     45

#define POSIX_SIGACTION  46
#define POSIX_SIGNAL     47
#define POSIX_RAISE      48
#define POSIX_KILL       49
#define POSIX_SIGPROCMASK     50

#define POSIX_STUBBED    99

#define PEDIGREE_LOGIN   101
#define PEDIGREE_SIGRET  102

#endif
