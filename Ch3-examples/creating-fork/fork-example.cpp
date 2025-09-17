#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
pid_t pid;
	/* fork a child process */
	pid = fork();
	if (pid < 0) { /* error occurres*/
		// fprintf allows printing in destination and message
		// stderr is typically unbuffered or line-buffered; ideal for conveying crit error info
		fprintf(stderr, "Fork Failed");
		return 1;
	}
	else if (pid == 0) { /* child process */
		// This is the key to outputting correctly in the hw3 assignment.
		execlp("/bin/ls", "ls", NULL);
	}
	else {/* parent process */
		/* parent will wait for the child to complete */
		wait(NULL);
		printf("Child Complete");
	}

	return 0;
}
