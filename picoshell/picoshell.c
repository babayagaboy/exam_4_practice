#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int picoshell(char **cmds[])
{
    int i = 0;
    int fd[2];
    pid_t pid;
    int last_fd = -1;

    while (cmds[i])
    {
        if (cmds[i + 1] && pipe(fd) == -1)
            return (1);
        pid = fork();
        if (pid == -1)
        {
            close(fd[0]);
            close(fd[1]);
            return (1);
        }
        if (pid == 0)
        {
            if (last_fd != -1)
            {
                if(dup2(last_fd, STDIN_FILENO) == -1)
                    return (1);
                close(last_fd);
            }
            if(dup2(fd[0], STDOUT_FILENO) == -1)
                return (1);
            close(fd[0]);
            execvp(cmds[i], cmds[i][0]);
            exit(1);
        }
        if (last_fd != -1)
        {
            ;
        }
        i++;
    }
    
    while (wait(NULL))
    {
        ;
    }
    
}

int main()
{
    
}