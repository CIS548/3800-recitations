#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

struct server_info
{
    int fd;
    struct sockaddr_in sin;
    socklen_t len;
};

static void *
handleNewConnection(void *arg);

void sigtermHandler(int sig);

struct server_info *configServer(char *host_addr, int port);
