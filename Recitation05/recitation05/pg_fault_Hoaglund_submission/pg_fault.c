#include "pg_fault.h"

/*
 * Function: getPageSize
 *
 * Purpose: Get the system page size
 */

int getPageSize()
{
  return (sysconf(_SC_PAGE_SIZE));
}

/*
 *
 * Function: sendMemoryRequest
 *
 * Purpose: Sending memory request to the server
 *
 * args:
 * int s: file descriptor of socket
 * int page_size: size of a page
 * int page: page number in the allocated memory
 *
 */
void sendMemoryRequest(int s, int page_size, int page)
{

  char buf[100];
  memset(buf, '\0', 100 * sizeof(char));
  sprintf(buf, "%d %d", page_size, page);

  int len = strlen(buf) + 1;

  send(s, buf, len, 0);
}

int connectToAddress(char *host_addr, int port)
{
  int s;
  if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0)
  {
    perror("simplex-talk: socket");
    exit(EXIT_FAILURE);
  }
  sock = s;

  /* Config the server address */
  struct sockaddr_in sin;
  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = inet_addr(host_addr);
  sin.sin_port = htons(port);

  /* Connect to the server */
  if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0)
  {
    perror("simplex-talk: connect");
    close(s);
    exit(EXIT_FAILURE);
  }
  return s;
}

/*
 * Function: faultHandlerThread
 *
 *
 *
 * args:
 * void * arg: going to get casted to a page_info struct
 * which contains the userfaultfd file descriptor, page size
 * of the system, and memory pointer of the memory which is being monitored.
 *
 * By passing in the memory pointer, when we have page faults, we can
 * use the starting memory and the memory which page faulted to find out
 * which page out of the memory being monitored experienced a page fault.
 *
 */

static void *
faultHandlerThread(void *arg)
{
  long uffd;
  static struct uffd_msg msg;
  struct uffdio_copy uffdio_copy;
  static char *page = NULL;
  int page_size;
  long starting_addr;
  unsigned long faulting_page;
  int faulting_pnum;

  struct page_info *p_info = (struct page_info *)arg;

  uffd = p_info->uffd;
  page_size = p_info->page_size;
  starting_addr = (long)p_info->mem_pointer;
  /*
   * Probably a redundant check but they had something similar in the demo.c file
   * This creates the page which will be populated with the TCP server information
   */
  if (page == NULL)
  {
    page = mmap(NULL, page_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  }

  if (page == MAP_FAILED)
  {
    perror("page mmap");
    exit(EXIT_FAILURE);
  }

  /*Going to connect to a server here */
  char *host_addr = "127.0.0.1";
  int port = 5000;

  /* Open a socket */
  int s = connectToAddress(host_addr, port);

  while (1)
  {
    int nready;
    struct pollfd pollfd;
    pollfd.fd = uffd;
    pollfd.events = POLLIN;
    /* blocks thread until there is a new action of on the file descriptor 
     * which is the userfaultfd
     */
    nready = poll(&pollfd, 1, -1);
    if (nready == -1)
    {
      perror("poll");
      exit(EXIT_FAILURE);
    }

    /* reads the userfaultfd */
    read(uffd, &msg, sizeof(msg));

    if (msg.event != UFFD_EVENT_PAGEFAULT)
    {
      fprintf(stderr, "Unexpected event on userfaultfd\n");
      exit(EXIT_FAILURE);
    }

    faulting_page = msg.arg.pagefault.address;
    /* calculated to send the page which faulted out of the memory which is being monitored */
    faulting_pnum = (faulting_page - starting_addr) / page_size;

    //Line below was another idea
    //To possibly get different information based on the calling thread
    // u_int64_t thread_id = msg.arg.pagefault.feat.ptid;
    sendMemoryRequest(s, page_size, faulting_pnum);

    char buffer[page_size];

    int l = recv(s, buffer, sizeof(buffer), 0);
    if (l < 0)
    {
      perror("recv");
      exit(EXIT_FAILURE);
    }

    void *ret = memcpy(page, buffer, page_size);
    if (ret < 0)
    {
      perror("memcpy");
      exit(EXIT_FAILURE);
    }

    /* actions to copy the information */

    uffdio_copy.src = (unsigned long)page;
    uffdio_copy.dst = (unsigned long)faulting_page & ~(page_size - 1);
    uffdio_copy.len = page_size;
    uffdio_copy.mode = 0;
    uffdio_copy.copy = 0;

    if (ioctl(uffd, UFFDIO_COPY, &uffdio_copy) == -1)
    {
      perror("copy");
      exit(EXIT_FAILURE);
    }
  }

  return NULL;
}

/*
 * Function: initUserfaultfd
 *
 * Purpose: initialized the userfaultfd
 *
 * args:
 * char *addr: The memory which we will have custom page fault behavior for
 * len: the size of the memory
 *
 */

long initUserfaultfd(char *addr, uint64_t len)
{
  long uffd; /* userfaultfd file descriptor */
  struct uffdio_api uffdio_api;
  struct uffdio_register uffdio_register;
  uffd = syscall(__NR_userfaultfd, O_CLOEXEC | O_NONBLOCK);
  if (uffd == -1)
  {
    perror("userfaultfd");
    exit(EXIT_FAILURE);
  }

  uffdio_api.api = UFFD_API;
  uffdio_api.features = UFFD_FEATURE_THREAD_ID;

  ioctl(uffd, UFFDIO_API, &uffdio_api);

  uffdio_register.range.start = (unsigned long)addr;
  uffdio_register.range.len = len;
  uffdio_register.mode = UFFDIO_REGISTER_MODE_MISSING;
  if (ioctl(uffd, UFFDIO_REGISTER, &uffdio_register) == -1)
  {
    perror("ioctl registers");
    exit(EXIT_FAILURE);
  }
  return uffd;
}

/*
 * Function: main
 *
 * Purpose: Run the program
 *
 * args:
 * int argc: number of command line arguments
 * char **argv: the command line arguments
 *
 *
 */

int main(int argc, char **argv)
{
  int num_q;
  int page_size;
  char *in;
  int brk;
  long uffd;
  char *addr;    /* Start of region handled by userfaultfd */
  uint64_t len;  /* Length of region handled by userfaultfd */
  pthread_t thr; /* ID of thread that handles page faults */
  int s;
  struct page_info *p_info;

  num_q = 4;
  page_size = getPageSize();

  len = strtoull("4", NULL, 0) * page_size;

  addr = mmap(NULL, len, PROT_READ | PROT_WRITE,
              MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  if (addr == MAP_FAILED)
  {
    perror("mmap");
    exit(EXIT_FAILURE);
  }

  uffd = initUserfaultfd(addr, len);

  p_info = malloc(sizeof(struct page_info));
  if (p_info == NULL)
  {
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  p_info->uffd = uffd;
  p_info->mem_pointer = (void *)addr;
  p_info->page_size = page_size;

  s = pthread_create(&thr, NULL, faultHandlerThread, (void *)p_info);
  if (s != 0)
  {
    perror("pthread");
    exit(EXIT_FAILURE);
  }
  brk = 1;
  int r_len;
  int input;
  char c;

  while (brk)
  {
    in = malloc(sizeof(char) * 10);
    fprintf(stderr, "\n\nInsert a number between 0 and 3 for a quote from a famous movie\n Enter -1 to exit\n");
    r_len = read(STDIN_FILENO, in, 10);
    in[r_len] = '\0';
    input = atoi(in);
    if (input == -1)
    {
      break;
    }
    else if (input < 0 || input > num_q - 1)
    {
      fprintf(stderr, "invalid input\n");
      continue;
    }

    for (int i = page_size * input; i < page_size * (input + 1); i++)
    {
      c = addr[i];
      fprintf(stderr, "%c", c);
      if (c == '.')
      {
        fprintf(stderr, "\n");
        i++;
      }
    }
  }
  close(sock);

  return 0;
}
