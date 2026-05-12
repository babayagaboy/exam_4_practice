#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int picoshell(char **cmds[])
{
    int fd[2];
    int i = 0;
    pid_t pid;
    int last_fd = -1;

    while (cmds[i])
    {
        if (cmds[i + 1] && pipe(fd) == -1)
            return (1);
        pid = fork();
        if (pid == -1)
        {
            if (cmds[i + 1])
            {
                close(fd[0]);
                close(fd[1]);
            }
            return(1);
        }
        if (pid == 0)
        {
            if (last_fd != -1)
            {
                if(dup2(last_fd, STDIN_FILENO) == -1)
                    exit(1);
                close(last_fd);
            }
            if(cmds[i + 1])
            {
                dup2(fd[1], STDOUT_FILENO);
                close(fd[0]);
                close(fd[1]);
            }    
            execvp(cmds[i][0], cmds[i]);
            exit(1);
        }
        if(last_fd != -1)
            close(last_fd);
        if(cmds[i + 1])
        {
            close(fd[1]);
            last_fd = fd[0];
        }
        i++;
    }
    while (wait(NULL) > 0)
    {
        ;
    }
    
    return (0);
}

// int main()
// {
//     char *cmd1[] = {"cat", "picoshell.c", NULL};
//     char *cmd2[] = {"cat", "-e", NULL};
//     char **cmds[] = {
//         cmd1,
//         cmd2,
//         NULL
//     };
//     picoshell(cmds);
// }
