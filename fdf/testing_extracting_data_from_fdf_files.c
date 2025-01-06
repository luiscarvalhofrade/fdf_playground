#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"

int main(int argc, char **argv)
{
    char **result;
    char *line;
    int i;
    int j;

    i = 0;
    if (argc != 2)
    {
        printf("Usage: %s <file_path>\n", argv[0]);
        return (1);
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return (1);
    }


    j = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        result = ft_split(line, ' ');
        while (i <= 4)
        {
            printf("point: (%d, %d)", i, j);
            i++;
        }
        j++;
        free(line);         // Free the line after processing
    }
    if (close(fd) == -1)
    {
        perror("Error closing file");
        return (1);
    }

    return (0);
}