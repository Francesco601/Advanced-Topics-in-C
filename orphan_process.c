// C program to illustrate the creation of an
// orphan process in operating systems programming.
// An orphan process is a process whose parent process
// has terminated and no longer exists in the process table



#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    // fork() Create a child process

    int pid = fork();
    if (pid > 0) {
        //getpid() returns process id
        // while getppid() will return parent process id
        printf("Parent process\n");
        printf("ID : %d\n\n", getpid());
    }
    else if (pid == 0) {
        printf("Child process\n");
        // getpid() will return process id of child process
        printf("ID: %d\n", getpid());
        // getppid() will return parent process id of child process
        printf("Parent -ID: %d\n\n", getppid());

        sleep(10);

        // At this point parent process has finished.
        // So if you  check parent process id
        // it will show a  different process id
        printf("\nChild process \n");
        printf("ID: %d\n", getpid());
        printf("Parent -ID: %d\n", getppid());
    }
    else {
        printf("Failed to create child process");
    }

    return 0;
}
