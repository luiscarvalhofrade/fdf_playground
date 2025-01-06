#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"

typedef struct s_point3d { 
    int x; 
    int y; 
    int z; 
}       t_point3d; 

int main(int argc, char **argv)
{
    t_point3d start;
    t_point3d end;
    char **result;
    char *line;
    int i;
    int j;
    int fd;

    if (argc != 2)
    {
        printf("Usage: %s <file_path>\n", argv[0]);
        return (1);
    }
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return (1);
    }
    i = 0;
    j = 0;
    line = get_next_line(fd);
    while (line)
    {
        i = 0;
        result = ft_split(line, ' ');
        while (i <= 8)
        {
            if (i == 0 && j ==0)
            {
                start.x = 0;
                start.y = 0;
                start.z = atoi(result[i]);
            }

            printf("(%d, %d, %s) ", i, j, result[i]);
            i++;
        }
        printf("\n");
        j++;
        free(line);    
        line = get_next_line(fd);     // Free the line after processing
    }
    if (close(fd) == -1)
    {
        perror("Error closing file");
        return (1);
    }
    end.x = (i - 1);
    end.y = (j - 1);
    end.z = atoi(result[i - 1]);

    return (0);
}