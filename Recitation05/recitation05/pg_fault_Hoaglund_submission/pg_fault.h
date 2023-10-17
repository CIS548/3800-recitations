#define _GNU_SOURCE
#include <inttypes.h>
#include <sys/types.h>
#include <stdio.h>
#include <linux/userfaultfd.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <poll.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/syscall.h>
#include <sys/ioctl.h>
#include <poll.h>

#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

static int sock;

struct page_info
{
    void *mem_pointer;
    long uffd;
    int page_size;
};

int getPageSize();

void sendMemoryRequest(int s, int page_size, int page_num);

static void *faultHandlerThread(void *arg);

long initUserfaultfd(char *addr, uint64_t len);

int connectToAddress(char *host_addr, int port);
