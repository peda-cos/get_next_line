#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int fd;
    char *line;
    int i = 1;

    while (i < argc)
    {
        fd = open(argv[i], O_RDONLY);
        while ((line = get_next_line(fd)) != NULL)
        {
            printf("%s\n", line);
            free(line);
        }
        close(fd);
        i++;
    }
    return 0;
}
