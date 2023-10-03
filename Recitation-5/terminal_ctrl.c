#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int childPid = 0;
void alarm_handler()
{
	alarm(3);
	if(tcgetpgrp(STDIN_FILENO) == getpgrp())
	{
		tcsetpgrp(STDIN_FILENO, childPid);
	} else {
		tcsetpgrp(STDIN_FILENO, getpgrp());
	}


}

void sigint_handler()
{

	if(!childPid)
	{
		fprintf(stderr, "Child Ctrl-C\n");
		return;
	}
	fprintf(stderr, "parent ctrl-C\n");
}
// allowing for stopping using ctrl-Z
void sigstp_handler()
{
	exit(0);
}


int main()
{
	char buf[100];
	// Is this needed?
	signal(SIGTTOU, SIG_IGN);
	
	signal(SIGALRM, alarm_handler);
	signal(SIGINT, sigint_handler);
	signal(SIGTSTP, sigstp_handler);
	childPid = fork();
	if(!childPid)
	{
		setpgrp();
	//	fprintf(stderr, "%d\n", getpgrp());
	while(1);
	} else {
		//fprintf(stderr, "%d\n", getpgrp());
	alarm(3);
		while(1) { /* 
			if(read(STDIN_FILENO, buf, 10) == 0)
			{
				exit(0);
			}*/
	/* just to show that anybody can write at a given time
			write(STDOUT_FILENO, "Hi\n", 4);
				sleep(1); */
		}
	}
}
