#include "pg_server.h"

/*
 * Function: sigtermHandler
 *
 * Purpose: handler sigterm signal and make sure to close
 * the socket so no longer run into the
 * address already in use error as we are using pkill
 * to close the server many times
 *
 * args:
 * int sig: the signal number
 *
 */

void sigtermHandler(int sig)
{
  if (sig == SIGTERM)
  {
    fprintf(stderr, "TCP server is going down\n");
    exit(0);
  }
}

/*
 * Function: handleNewConnection
 *
 * Purpose: handle a new tcp connection within a unique thread
 *
 * args:
 * void *arg: gets casted to a long which is the file descriptor of the
 * new connection
 *
 */
static void *
handleNewConnection(void *arg)
{
  int page_size;
  int page_num;
  long new_s;
  int len;
  char *buf;
  char *page;
  int fd;
  off_t offset;
  size_t amount_to_read;

  offset =0;
  amount_to_read = 0;


  fd = open("quotes.txt", O_RDONLY, 0777);

  new_s = (long)*((long *)arg);
  free(arg);
  while (1)
  {
    buf = malloc(sizeof(char) * 10);
    len = recv(new_s, buf, sizeof(buf), 0);
    if (len < 0)
    {
      perror("recv");
      exit(EXIT_FAILURE);
    }
    else if (len == 0)
    {
      break;
    }
    /* 
     *
     * bytes star wars quote: offset 0, length 742
     * bytes harry potter quote: offset 743, length 482
     * devil wears prada quote: offset 1225, length 308
     * Lord of the rings: offset 1533, length rest of file
     */

    page_size = atoi(strtok(buf, " "));
    page_num = atoi(strtok(NULL, " "));

    if(page_num == 0) 
    {
      offset = 0;
      amount_to_read = 742;
    } else if (page_num == 1)
    {
      offset = 743;
      amount_to_read = 482;
    } else if (page_num == 2)
    {
      offset = 1225;
      amount_to_read = 308;
    } else if (page_num == 3)
    {
      offset = 1533;
      amount_to_read = page_size -1;
    }



    page = malloc(page_size * sizeof(char));
    memset(page, 0, page_size);
    int read = pread(fd, page, amount_to_read, offset);
    if(read < 0) {
      perror("pread");
      exit(EXIT_FAILURE);
    }
    page[page_size - 1] = '\0';

    send(new_s, page, page_size, 0);
    free(buf);
    free(page);
  }
  close(new_s);
  close(fd);

  return NULL;
}

/*
 * Function: configServer
 *
 * Purpose: configure the TCP server
 *
 * args:
 * char *host_addr: the host address which will be where it is hosted
 * int port: the port the server will be on
 *
 */

struct
    server_info *
    configServer(char *host_addr, int port)
{
  int option = 1;
  /*setup passive open */
  struct server_info *server;
  server = malloc(sizeof(struct server_info));

  if ((server->fd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
  {
    perror("simplex-talk: socket");
    exit(1);
  }

  setsockopt(server->fd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

  /* Config the server address */
  server->sin.sin_family = AF_INET;
  server->sin.sin_addr.s_addr = inet_addr(host_addr);
  server->sin.sin_port = htons(port);
  // Set all bits of the padding field to 0
  memset(server->sin.sin_zero, '\0', sizeof(server->sin.sin_zero));

  /* Bind the socket to the address */
  if ((bind(server->fd, (struct sockaddr *)&server->sin, sizeof(server->sin))) < 0)
  {
    perror("simplex-talk: bind");
    exit(EXIT_FAILURE);
  }

  listen(server->fd, 100);
  server->len = sizeof(server->sin);
  return server;
}

/*
 * Function: main
 *
 * purpose: run the program
 *
 * args:
 * int argc: number of command line arguments
 * char ** argv: command line arguments
 *
 */

int main(int argc, char **argv)
{
  pthread_t thr;
  long *new_s;
  char *host_addr;
  int port;
  int r;
  struct server_info *server;

  host_addr = "127.0.0.1";
  port = 5000;

  server = configServer(host_addr, port);
  signal(SIGTERM, sigtermHandler);
  while (1)
  {
    new_s = malloc(sizeof(long));
    if (new_s == NULL)
    {
      perror("malloc");
      exit(EXIT_FAILURE);
    }

    if ((*new_s = accept(server->fd, (struct sockaddr *)&server->sin, &server->len)) < 0)
    {
      perror("simplex-talk: accept");
      exit(1);
    }

    /* Create a new thread to handle every new connection*/
    r = pthread_create(&thr, NULL, handleNewConnection, (void *)new_s);
    if (r != 0)
    {
      perror("pthread");
      exit(EXIT_FAILURE);
    }
  }
  free(server);
}
