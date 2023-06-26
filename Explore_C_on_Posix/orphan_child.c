#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


//Here is an example with an orphan child process, an orphan process refers to a child process that
//continues to run even after its parent process has finished or terminated.
//When this happens,the orphaned child process is adopted by the init process (usually with process ID >

//Orphan processes are adopted by the init process to ensure that they are not left as "zombie" process>
//which consume system resources without being properly cleaned up.
//The init process becomes the new parent of the orphaned processes and takes responsibility for their >

//Just be sure to handle child processes properly in your programs or scripts to avoid leaving orphan p>
//This typically involves implementing mechanisms to wait for child process completion,
//handling signals, and properly terminating child processes before the parent process exits.


int main() {
        pid_t child_pid = fork();
        if (child_pid > 0)
        {
        printf("Parent process\n");   // Parent process
        sleep(1);
        printf("Parent process exiting\n");
        printf("Child process (PID: %d)\n", getpid());
        printf("Child process's parent (PPID): %d\n", getppid());

        }

        else if (child_pid == 0)
        {
        sleep(4); // Child process
        printf("Child process (PID: %d)\n", getpid());
        printf("Child process's parent (PPID): %d\n", getppid());
        printf("Child process exiting\n");
        }
        else {
                fprintf(stderr, "Fork failed\n");  // Forking failed
       return 1;
   }
   return 0;
}
