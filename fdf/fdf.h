#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "./minilibx-linux/mlx.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_src
{
	int	x;
	int	y;
	int	z;
}		t_src;

typedef struct s_dst
{
	int	x;
	int	y;
}		t_dst;

t_dst	set_dst_pts(t_src src);

#endif