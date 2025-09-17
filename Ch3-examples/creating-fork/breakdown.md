# Breakdown of Code
In UNIX, each process is identified by its PID. A new process is created by the fork() system call. This
mechanism allows the parent process to communicate easily with its child process. Both processess continue
execution at the instruction after the fork(), with one difference: the return code for the fork() is zero
for the new (child) process, whereas the (nonzero) PID of the child is returned to the parent.
