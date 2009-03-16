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

#include "syscallNumbers.h"

#include "errno.h"
#define errno (*__errno())
extern int *__errno (void);
 
// Define errno before including syscall.h.
#include "syscall.h"

extern void *malloc(int);
extern void free(void*);
extern void strcpy(char*,char*);

extern void printf(char*,...);
extern void sprintf(char*, char*,...);

#define MAXNAMLEN 255

#define STUBBED(str) syscall1(POSIX_STUBBED, (int)(str)); \
  errno = ENOSYS;

struct dirent
{
  char d_name[MAXNAMLEN];
  int d_ino;
};

typedef struct ___DIR
{
  int fd;
  struct dirent ent;
} DIR;

struct timeval {
  unsigned int tv_sec;
  unsigned int tv_usec;
};

struct timezone {
  int tz_minuteswest;
  int tz_dsttime;
};

struct sigevent {
};

struct passwd {
	char	*pw_name;		/* user name */
	char	*pw_passwd;		/* encrypted password */
	int	pw_uid;			/* user uid */
	int	pw_gid;			/* user gid */
	char	*pw_comment;		/* comment */
	char	*pw_gecos;		/* Honeywell login info */
	char	*pw_dir;		/* home directory */
	char	*pw_shell;		/* default shell */
};

struct  stat
{
  int   st_dev;
  int   st_ino;
  int   st_mode;
  int   st_nlink;
  int   st_uid;
  int   st_gid;
  int   st_rdev;
  int   st_size;
  int   st_atime;
  int   st_mtime;
  int   st_ctime;
};

struct sockaddr
{
  unsigned int sa_family;
  char sa_data[14];
};

struct in_addr
{
  unsigned int s_addr;
};

struct sigaction
{
};

int ftruncate(int a, int b)
{
  STUBBED("ftruncate");
  return -1;
}

int mkdir(const char *p)
{
  STUBBED("mkdir")
  return -1;
}

int close(int file)
{
  return syscall1(POSIX_CLOSE, file);
}

int _execve(char *name, char **argv, char **env)
{
  return syscall3(POSIX_EXECVE, name, argv, env);
}

void _exit(int val)
{
  syscall1(POSIX_EXIT, val);
}

int fork()
{
  return syscall0(POSIX_FORK);
}

int fstat(int file, struct stat *st)
{
  return syscall2(POSIX_FSTAT, file, st);
}

int getpid()
{
  return syscall0(POSIX_GETPID);
}

int _isatty(int file)
{
  STUBBED("_isatty");
  return 1;
}

int kill(int pid, int sig)
{
  STUBBED("kill");
  return -1;
}

int link(char *old, char *_new)
{
  STUBBED("link");
  return -1;
}

int lseek(int file, int ptr, int dir)
{
  return syscall3(POSIX_LSEEK, file, ptr, dir);
}

int open(const char *name, int flags, int mode)
{
  return syscall3(POSIX_OPEN, name, flags, mode);
}

int read(int file, char *ptr, int len)
{
  return syscall3(POSIX_READ, file, ptr, len);
}

int sbrk(int incr)
{
  return syscall1(POSIX_SBRK, incr);
}

int stat(const char *file, struct stat *st)
{
  return syscall2(POSIX_STAT, file, st);
}

#ifndef PPC_COMMON
int times(void *buf)
{
  STUBBED("times");
  return -1;
}
#else
/* PPC has times() defined in terms of getrusage. */
int getrusage(int target, void *buf)
{
  STUBBED("getrusage");
  return -1;
}
#endif

int unlink(char *name)
{
  STUBBED("unlink");
  return -1;
}

int wait(int *status)
{
  return waitpid(-1, status, 0);
}

int waitpid(int pid, int *status, int options)
{
  return syscall3(POSIX_WAITPID, pid, status, options);
}

int write(int file, char *ptr, int len)
{
  return syscall3(POSIX_WRITE, file, ptr, len);
}

int lstat(char *file, struct stat *st)
{
  return syscall2(POSIX_STAT, file, st);
}

DIR *opendir(const char *dir)
{
  DIR *p = malloc(sizeof(DIR));
  p->fd = syscall2(POSIX_OPENDIR, dir, &p->ent);
  return p;
}

struct dirent *readdir(DIR *dir)
{
  if (syscall2(POSIX_READDIR, dir->fd, &dir->ent) != -1)
    return &dir->ent;
  else
    return 0;
}

void rewinddir(DIR *dir)
{
  syscall2(POSIX_REWINDDIR, dir->fd, &dir->ent);
}

int closedir(DIR *dir)
{
  syscall1(POSIX_CLOSEDIR, dir->fd);
  free(dir);
  return 0;
}

int tcgetattr(int fd, void *p)
{
  return syscall2(POSIX_TCGETATTR, fd, p);
}

int tcsetattr(int fd, int optional_actions, void *p)
{
  return syscall3(POSIX_TCSETATTR, fd, optional_actions, p);
}

int mkfifo(const char *_path, int __mode)
{
  STUBBED("mkfifo");
  return -1;
}

int gethostname(char *name, int len)
{
  STUBBED("gethostname");
  strcpy(name, "pedigree");
  return 0;
}

int ioctl(int fd, int command, void *buf)
{
  return syscall3(POSIX_IOCTL, fd, command, buf);
}

int tcflow(int fd, int action)
{
  STUBBED("tcflow");
  return 0;
}

int tcflush(int fd, int queue_selector)
{
  STUBBED("tcflush");
  return 0;
}

int tcdrain(int fd)
{
  STUBBED("tcdrain");
  return -1;
}

int gettimeofday(struct timeval *tv, struct timezone *tz)
{  
  syscall2(POSIX_GETTIMEOFDAY, (int)tv, (int)tz);

  return 0;
}

/*long sysconf(int name)
{
  STUBBED("sysconf");
  errno = EINVAL;
  return -1;
}*/

int getuid()
{
  STUBBED("getuid");
  return 0;
}

int getgid()
{
  STUBBED("getgid");
  return 0;
}

int geteuid()
{
  STUBBED("geteuid");
  return 0;
}

int getegid()
{
  STUBBED("getegid");
  return 0;
}

int getppid()
{
  STUBBED("getppid");
  return 0;
}

const char * const sys_siglist[] = {
  "Hangup",
  "Interrupt",
  "Quit",
  "Illegal instruction",
  "Trap",
  "IOT",
  "Abort",
  "EMT",
  "Floating point exception",
  "Kill",
  "Bus error",
  "Segmentation violation",
  "Bad argument to system call",
  "Pipe error",
  "Alarm",
  "Terminate" };

char *strsignal(int sig)
{
  if (sig < 16)
    return (char*)sys_siglist[sig];
  else
  return (char*)"Unknown";
}

int setuid(int uid)
{
  STUBBED("setuid");
  errno = EINVAL;
  return -1;
}

int setgid(int gid)
{
  STUBBED("setgid");
  errno = EINVAL;
  return -1;
}

unsigned int sleep(unsigned int seconds)
{
  STUBBED("sleep");
  return 0;
}

unsigned int alarm(unsigned int seconds)
{
  STUBBED("alarm");
  return 0;
}

int umask(int mask)
{
  STUBBED("umask");
  return 0;
}

int chmod(const char *path, int mode)
{
  STUBBED("chmod");
  errno = ENOENT;
  return -1;
}

int chown(const char *path, int owner, int group)
{
  STUBBED("chown");
  errno = ENOENT;
  return -1;
}

int utime(const char *path, const struct utimbuf *times)
{
  STUBBED("utime");
  errno = ENOENT;
  return -1;
}

int sigaction(int sig, const struct sigaction *act, struct sigaction *oact)
{
  STUBBED("sigaction");
  errno = ENOSYS;
  return -1;
}

int dup2(int fildes, int fildes2)
{
  STUBBED("dup2");
  return -1;
}

int access(const char *path, int amode)
{
  STUBBED("access");
  errno = ENOENT;
  return 0;
}

const char * const sys_errlist[] = {};
const int sys_nerr = 0;
long timezone;

long pathconf(const char *path, int name)
{
  STUBBED("pathconf");
  return 0;
}

long fpathconf(int filedes, int name)
{
  STUBBED("fpathconf");
  return 0;
}

int cfgetospeed(const struct termios *t)
{
  STUBBED("cfgetospeed");
  return 0;
}

int cfgetispeed(const struct termios *t)
{
  STUBBED("cfgetispeed");
  return 0;
}

int cfsetospeed(const struct termios *t, int speed)
{
  STUBBED("cfsetospeed");
  return 0;
}

int cfsetispeed(const struct termios *t, int speed)
{
  STUBBED("cfsetispeed");
  return 0;
}


int select(int nfds, struct fd_set * readfds,
                     struct fd_set * writefds, struct fd_set * errorfds,
                     struct timeval * timeout)
{
  return syscall5(POSIX_SELECT, nfds, readfds, writefds, errorfds, timeout);
}

void setgrent()
{
  STUBBED("setgrent");
}

void endgrent()
{
  STUBBED("endgrent");
}

struct group *getgrent()
{
  STUBBED("getgrent");
  errno = ENOSYS;
  return 0;
}

int chdir(const char *path)
{
  return syscall1(POSIX_CHDIR, path);
}

int dup(int fileno)
{
  STUBBED("dup");
  return -1;
}

int pipe(int filedes[2])
{
  STUBBED("pipe");
  return -1;
}

int fcntl(int fildes, int cmd, ...)
{
  STUBBED("fcntl");
  errno = ENOSYS;
  return -1;
}

int sigprocmask(int how, int set, int oset)
{
  STUBBED("sigprocmask");
  return -1;
}

int fchown(int fildes, int owner, int group)
{
  STUBBED("fchown");
  return -1;
}

int rmdir(const char *path)
{
  STUBBED("rmdir");
  return -1;
}

int socket(int domain, int type, int protocol)
{
  return syscall3(POSIX_SOCKET, domain, type, protocol);
}

int connect(int sock, const struct sockaddr* address, unsigned long addrlen)
{
  return syscall3(POSIX_CONNECT, sock, (int) address, (int) addrlen);
}

int send(int sock, const void * buff, unsigned long bufflen, int flags)
{
  return syscall4(POSIX_SEND, sock, (int) buff, (int) bufflen, flags);
}

int recv(int sock, void * buff, unsigned long bufflen, int flags)
{
  return syscall4(POSIX_RECV, sock, (int) buff, (int) bufflen, flags);
}

int accept(int sock, struct sockaddr* remote_addr, unsigned long* addrlen)
{
  return syscall3(POSIX_ACCEPT, sock, (int) remote_addr, (int) addrlen);
}

int bind(int sock, const struct sockaddr* local_addr, unsigned long addrlen)
{
  return syscall3(POSIX_BIND, sock, (int) local_addr, (int) addrlen);
}

int getpeername(int sock, struct sockaddr* addr, unsigned long* addrlen)
{
  STUBBED("getpeername");
  return -1;
}

int getsockname(int sock, struct sockaddr* addr, unsigned long* addrlen)
{
  STUBBED("getsockname");
  return -1;
}

int getsockopt(int sock, int level, int optname, void* optvalue, unsigned long* optlen)
{
  STUBBED("getsockopt");
  return -1;
}

int listen(int sock, int backlog)
{
  return syscall2(POSIX_LISTEN, sock, backlog);
}

long recvfrom(int sock, void* buff, unsigned long bufflen, int flags, struct sockaddr* remote_addr, unsigned long* addrlen)
{
  STUBBED("recvfrom");
  return -1;
}

long recvmsg(int sock, struct msghdr* msg, int flags)
{
  STUBBED("recvmsg");
  return -1;
}

long sendmsg(int sock, const struct msghdr* msg, int flags)
{
  STUBBED("sendmsg");
  return -1;
}

long sendto(int sock, const void* buff, unsigned long bufflen, int flags, const struct sockaddr* remote_addr, unsigned long* addrlen)
{
  STUBBED("sendto");
  return -1;
}

int setsockopt(int sock, int level, int optname, const void* optvalue, unsigned long optlen)
{
  STUBBED("setsockopt");
  return -1;
}

int shutdown(int sock, int how)
{
  STUBBED("shutdown");
  return -1;
}

int sockatmark(int sock)
{
  STUBBED("sockatmark");
  return -1;
}

int socketpair(int domain, int type, int protocol, int sock_vec[2])
{
  STUBBED("socketpair");
  return -1;
}

char* inet_ntoa(struct in_addr addr)
{
  static char buff[16];
  sprintf(buff, "%u.%u.%u.%u", addr.s_addr & 0xff, (addr.s_addr & 0xff00) >> 8, (addr.s_addr & 0xff0000) >> 16, (addr.s_addr & 0xff000000) >> 24);
  return buff;
}

struct hostent* gethostbyaddr(const void *addr, unsigned long len, int type)
{
  STUBBED("gethostbyaddr");
  return 0;
}

struct hostent* gethostbyname(const char *name)
{
  STUBBED("gethostbyname");
  return 0;
}

struct servent* getservbyname(const char *name, const char *proto)
{
  STUBBED("getservbyname");
  return 0;
}

int getgrnam()
{
  STUBBED("getgrnam");
  return 0;
}

int getgrgid()
{
  STUBBED("getgrgid");
  return 0;
}

int symlink()
{
  STUBBED("symlink");
  return 0;
}

int mknod()
{
  STUBBED("mknod");
  return 0;
}

int fsync()
{
  STUBBED("fsync");
  return 0;
}

int inet_pton()
{
  STUBBED("inet_pton");
  return -1;
}

void* popen(const char *command, const char *mode)
{
  STUBBED("popen");
  return 0;
}

int pclose(void* stream)
{
  STUBBED("pclose");
  return 0;
}
