#include "apue.h"
#include <stdio.h>

int
main(void)
{
	pid_t	pid;

	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid != 0) {		/* parent */
        fprintf(stdout, "PARENT(pid:%d)\n", (int)getpid());  /* Print parent process */
		sleep(2);
		exit(2);				/* terminate with exit status 2 */
	}

	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid != 0) {		/* first child */
        fprintf(stdout, "CHILD1(pid:%d)\n", (int)getpid());  /* Print child process */
		sleep(4);
		abort();				/* terminate with core dump */
	}

	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid != 0) {		/* second child */
        fprintf(stdout, "CHILD2(pid:%d)\n", (int)getpid());  /* Print second child process */
		execl("/bin/dd", "dd", "if=/etc/passwd", "of=/dev/null", NULL);
		exit(7);				/* shouldn't get here */
	}

	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid != 0) {		/* third child */
        fprintf(stdout, "CHILD3(pid:%d)\n", (int)getpid()); /* Print third child process */
		sleep(8);
		exit(0);				/* normal exit */
	}

	sleep(6);					/* fourth child */
    fprintf(stdout, "CHILD4(pid:%d)\n", (int)getpid()); /* Print fourth child process */
	kill(getpid(), SIGKILL);	/* terminate w/signal, no core dump */
	exit(6);					/* shouldn't get here */
}
