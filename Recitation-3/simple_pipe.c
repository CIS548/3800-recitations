#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main()
{
	int pipefd[2]; //write end = pipefd[1], read end = pipefd[0]
	pid_t cpid;
	char buf;

	if(pipe(pipefd) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	cpid = fork();
	if(cpid == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (cpid == 0) { // child
	close(pipefd[1]);
	while(read(pipefd[0], &buf, 1) > 0)
		write(STDOUT_FILENO, &buf, 1);
	write(STDOUT_FILENO, "\n", 1);
	close(pipefd[0]);
	exit(EXIT_SUCCESS);
	} else {
		close(pipefd[0]);
		write(pipefd[1], "hi", 3);
		close(pipefd[1]);
		wait(NULL);
		exit(EXIT_SUCCESS);
	}
}
