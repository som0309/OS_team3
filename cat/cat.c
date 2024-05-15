#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

void ft_printf(void)
{
    char buf[1024];
    int ret;

    ret = 1;
    while (ret)
    {
        ret = read(0, buf, 1024);
        write(1, buf, ret);
    }
}

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (*str++)
        i++;
    return (i);
}

int main(int argc, char *argv[])
{
    int fd;
    char buf[1024];
    int ret;
    int i;

    ret = 1;
    i = 0;
    if (argc == 1)
        ft_printf();
    else
    {
        while (++i < argc)
        {
            fd = open(argv[i], O_RDONLY);
            ret = 1;
            if (fd == -1)
            {
                write(2, "cat: ", 5);
                write(2, argv[i], ft_strlen(argv[i]));
                write(2, ": ", 2);
                write(2, strerror(errno), ft_strlen(strerror(errno)));
            }
            while (ret)
            {
                ret = read(fd, buf, 1024);
                if (buf[0] == 0)
                    break;
                write(1, buf, ret);
            }
            close(fd);
        }
    }
    write(1, "\n", 1);
}
