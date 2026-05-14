#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <ctype.h>

char *s;
int sum();
int prod();
int factor();

void    printerr(int c)
{
    if (c)
        printf("Unexpected token '%c'", c);
    else
        printf("Unexpected end of input");
}

int sum()
{
    int a = prod();
    while (*s == '+')
    {
        s++;
        a += prod();
    }
    return (a);
}

int prod()
{
    int a = factor();
    while (*s == '*')
    {
        s++;
        a *= factor();
    }
    return (a);
}

int factor()
{
    int n = 0;
    if (isdigit(*s))
        return(*s++ - '0');
    while (*s == '(')
    {
        s++;
        n = sum();
        s++;
    }
    return(n);
}

int main(int ac, char **av)
{
    if (ac != 2)
        return (1);
    s = av[1];
    // if (!check())
    //     return (1);
    printf("%d", sum());
}