#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <mlx.h>

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

t_dst set_dst_pts(t_src src)
{
    t_dst	dst;
	double angle;
    double radians;

	angle = 120.0;
    radians = angle * M_PI / 180.0;
	dst.x = src.x * cos(radians) + src.y * cos(radians + 2) + src.z * cos(radians - 2);
	dst.y = src.x * sin(radians) + src.y * sin(radians + 2) + src.z * sin(radians - 2);
	return (dst);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int main(void)
{
    t_src   src1;
    t_src   src2;
    t_src   src3;
    t_src   src4;
    t_src   src5;
    t_src   src6;
    t_src   src7;
    t_src   src8;
    t_src   src9;
    t_dst   dst1;
    t_dst   dst2;
    t_dst   dst3;
    t_dst   dst4;
    t_dst   dst5;
    t_dst   dst6;
    t_dst   dst7;
    t_dst   dst8;
    t_dst   dst9;
    void	*mlx;
	void	*mlx_win;
	t_data	img;

    src1.x = 0;
    src1.y = 0;
    src1.z = 0;

    src2.x = 1;
    src2.y = 0;
    src2.z = 0;

    src3.x = 2;
    src3.y = 0;
    src3.z = 0;

    src4.x = 0;
    src4.y = 1;
    src4.z = 0;

    src5.x = 1;
    src5.y = 1;
    src5.z = 1;

    src6.x = 2;
    src6.y = 1;
    src6.z = 0;

    src7.x = 0;
    src7.y = 2;
    src7.z = 0;

    src8.x = 1;
    src8.y = 2;
    src8.z = 0;

    src9.x = 2;
    src9.y = 2;
    src9.z = 0;

    dst1 = set_dst_pts(src1);
    dst2 = set_dst_pts(src2);
    dst3 = set_dst_pts(src3);
    dst4 = set_dst_pts(src4);
    dst5 = set_dst_pts(src5);
    dst6 = set_dst_pts(src6);
    dst7 = set_dst_pts(src7);
    dst8 = set_dst_pts(src8);
    dst9 = set_dst_pts(src9);

    mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 20, 20, "Hello world!");
	img.img = mlx_new_image(mlx, 20, 20);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
    // my_mlx_pixel_put(&img, src1.x, src1.y, 0x00FF0000);
    // my_mlx_pixel_put(&img, src2.x, src2.y, 0x00FF0000);
	// my_mlx_pixel_put(&img, src3.x, src3.y, 0x00FF0000);
    // my_mlx_pixel_put(&img, src4.x, src4.y, 0x00FF0000);
    // my_mlx_pixel_put(&img, src5.x, src5.y, 0x00FF0000);
	// my_mlx_pixel_put(&img, src6.x, src6.y, 0x00FF0000);
    // my_mlx_pixel_put(&img, src7.x, src7.y, 0x00FF0000);
    // my_mlx_pixel_put(&img, src8.x, src8.y, 0x00FF0000);
	// my_mlx_pixel_put(&img, src9.x, src9.y, 0x00FF0000);
    my_mlx_pixel_put(&img, dst1.x, dst1.y, 0x00FF0000);
    my_mlx_pixel_put(&img, dst2.x, dst2.y, 0x00FF0000);
	my_mlx_pixel_put(&img, dst3.x, dst3.y, 0x00FF0000);
    my_mlx_pixel_put(&img, dst4.x, dst4.y, 0x00FF0000);
    my_mlx_pixel_put(&img, dst5.x, dst5.y, 0x00FF0000);
	my_mlx_pixel_put(&img, dst6.x, dst6.y, 0x00FF0000);
    my_mlx_pixel_put(&img, dst7.x, dst7.y, 0x00FF0000);
    my_mlx_pixel_put(&img, dst8.x, dst8.y, 0x00FF0000);
	my_mlx_pixel_put(&img, dst9.x, dst9.y, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}