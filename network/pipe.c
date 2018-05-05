#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define STDIN_OUT 1
#define STDIN_IN  0
int main()
{
    int fd[2];
    if(pipe(fd)==0)
    {
        if(fork()==0)
        {
            //child process
            close(1);
            dup2(fd[1],STDIN_OUT);
            close(fd[0]);
            execlp("ls","ls","-l",NULL);
        }
        else
        {
            //father process
            close(0);
            dup2(fd[0],STDIN_IN);
            close(fd[1]);
            execlp("wc","wc","-l",NULL);
        }
    }
    return 0;
}
