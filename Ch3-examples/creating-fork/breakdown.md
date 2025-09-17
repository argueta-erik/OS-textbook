# Breakdown of Process
In UNIX, each process is identified by its PID. A new process is created by the fork() system call. This
mechanism allows the parent process to communicate easily with its child process. Both processess continue
execution at the instruction after the fork(), with one difference: the return code for the fork() is zero
for the new (child) process, whereas the (nonzero) PID of the child is returned to the parent.  

After fork() system call, one of the two processes typically uses the exec() system call to replace the
process's memory space with a new program. The exec() system call loads a binary file into memory 
(destroying the memory image of the program containing the exec() system call) and starts its execution. 
In this manner, the two processes are able to communicate and then go their separate ways. The parent
can then create more children; or, if it has nothing to do while the child rund, it cann issue a wait() 
system call to move itself off the ready queue until the termination of the child. Because the call
to exec() overlays the process's address space with a new program, the call to exec() does not return
control unless an error occurs.  

# Breakdown of Code
Here, we have two different processes running copies of the same program. The only difference is that
the value of PID for the child process is ZERO (in fact, it is the actual PID of the child process). 
The child process inherits privileges and scheduling attributes from the parent, as well certain
resources, such as open files. The child process then overlays its address space using the UNIX 
command /bin/ls using the execlp() system call. The parent waits for the child processs to complete with
the wait() system call. When teh child process completes, the parent process resumes from the wait(),
where it completes using the exit() system call.  

```
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

```
