#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int ft_popen(const char *file, char *const argv[], char type)
{
    int fd[2];
    pid_t pid;

    if(!file || !argv || !argv[0] || (type != 'r' && type != 'w'))
        return (-1);
    if(pipe(fd) == -1)
        return (-1);
    pid = fork();
    if (pid < 0)
    {
        close(fd[0]);
        close(fd[1]);
        exit (-1);
    }
    if (pid == 0)
    {
        if (type == 'r')
        {
            if(dup2(fd[1], STDOUT_FILENO) < 0)
            {
                close(fd[0]);
                close(fd[1]);
                exit(1);
            }
        }
        if (type == 'w')
        {
            if(dup2(fd[0], STDIN_FILENO) < 0)
            {
                close(fd[0]);
                close(fd[1]);
                exit(1);
            }
        }
        close(fd[0]);
        close(fd[1]);
        execvp(file, argv);
        exit(1);
    }
    if (type == 'r')
        return(close(fd[1]), fd[0]);
    if (type == 'w')
        return(close(fd[0]), fd[1]);
    return(-1);
}

// int main()
// {
//     int  fd;
//     char c;

//     fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
//     while (read(fd, &c, 1) > 0)
//         write(1, &c, 1);
//     return (0);
// }