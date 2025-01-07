#ifndef FDF_H
# define FDF_H

# ifndef SCREEN_WIDTH
#  define SCREEN_WIDTH 1024
# endif
# ifndef SCREEN_HEIGHT
#  define SCREEN_HEIGHT 768
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_3d_pt
{
	int x;
	int y;
	int z;
}   t_3d_pt;

typedef struct s_r_c
{
	int	rows;
	int	cols;
}		t_r_c;

typedef struct s_list
{
	char			*content;
	struct s_list	*next_node;
}					t_list;

char	*get_next_line(int fd);
char	**ft_split(char const *s, char c);

int		ft_found_new_line(t_list *list);
int		ft_len_of_new_line(t_list *list);

void	ft_copy_string(t_list *list, char *str);
void	ft_free(t_list **list, t_list *clean_node, char *buffer);

t_list	*ft_find_last_node(t_list *list);

t_r_c num_rows_and_cols(char *map);

int	**convert_map_matrix(char *map);

char	**ft_split(char const *s, char c);

#endif