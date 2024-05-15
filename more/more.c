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

void more(char *filename)
{
    int fd;
    char buf[1024];
    int ret;
    int line_count = 0;
    char c;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        write(2, "more: ", 6);
        write(2, filename, ft_strlen(filename));
        write(2, ": ", 2);
        write(2, strerror(errno), ft_strlen(strerror(errno)));
        return;
    }

    while ((ret = read(fd, buf, 1024)) > 0)
    {
        write(1, buf, ret);
        for (int i = 0; i < ret; i++)
        {
            if (buf[i] == '\n')
                line_count++;
            if (line_count >= 20)
            {
                line_count = 0;
                write(1, "\n--more--\n", 10);
                do
                {
                    read(0, &c, 1);
                    if (c == 'q' || c == 'Q')
                    {
                        close(fd);
                        return;
                    }
                    else if (c == '\n')
                    {
                        break;
                    }
                } while (c != ' ' && c != 'f');
            }
        }
    }
    close(fd);
}

int main(int argc, char *argv[])
{
    if (argc == 1)
        ft_printf();
    else
    {
        for (int i = 1; i < argc; i++)
            more(argv[i]);
    }
    return 0;
}