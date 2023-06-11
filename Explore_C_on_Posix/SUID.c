#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


//This code uses SUID to change the effective user of a file while execution:
//The Real UID represents the user identity of the process, which is inherited from the user who launched the process.
//The SUID bit, if set on an executable file,
//allows the process to temporarily assume the identity of the file owner (SUID UID) when it's executed.

//The Effective UID (EUID) is the effective user identity of the process.
//It determines the privileges and permissions the process has while running. By default, the EUID is the same as the Real UID. However,
//if the SUID bit is set on an executable, the EUID can change to the SUID UID when the process is executed.

int main (void)
{
    pid_t f = fork();
    uid_t uid, euid, suid;



    switch (f)
    {
        case -1:
            perror("Error while forking");
            exit(1);
            break;
        case 0:
                 // get the current user IDs
		getresuid(&uid, &euid, &suid);

    		printf("Before setting the suid:\n");
   		printf("Real UID: %d\n", uid);
    		printf("Effective UID: %d\n", euid);
    		printf("Saved UID: %d\n", suid);

            // Change the effective and saved user IDs to 1000
            if (setresuid(1000, 1000, 1000) == -1)
            {
                perror("setresuid failed!\n");
                exit(1);
            }


            // Get the updated user IDs
            getresuid(&uid, &euid, &suid);
            printf("\nAfter setresuid:\n");
            printf("Real UID: %d\n", uid);
            printf("Effective UID: %d\n", euid);
            printf("Saved UID: %d\n\n", suid);
            fflush(stdout);

            // Execute a program within the child with SUID 1000
            execl("/usr/bin/ls", "/usr/bin/ls", NULL);
            printf("ERROR: execl failed\n");
            break;

        default:
            wait(NULL);
            printf("\nChild is successfully finished\n");
            fflush(stdout);
            break;
    }

    return 0;
}
