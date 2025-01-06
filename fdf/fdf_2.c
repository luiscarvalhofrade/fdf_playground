#include <fcntl.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <mlx.h>
#include <math.h> 

typedef struct  s_data { 
    void    *img; 
    char    *addr; 
    int     bits_per_pixel; 
    int     line_length; 
    int     endian; 
}               t_data; 

typedef struct s_point3d { 
    int x; 
    int y; 
    int z; 
}       t_point3d; 

typedef struct s_point2d { 
    int x; 
    int y; 
}       t_point2d; 

t_point2d isometric_projection(t_point3d point) {
    t_point2d projected;

    // Isometric projection angles (in degrees)
    double angle_x = 30.0;
    double angle_y = 30.0; 

    // Convert angles to radians
    double radians_x = angle_x * M_PI / 180.0;
    double radians_y = angle_y * M_PI / 180.0;

    // Isometric projection transformation (simplified)
    projected.x = (int)(point.x * cos(radians_x) - point.y * sin(radians_x)); 
    projected.y = (int)(point.y * cos(radians_y) - point.z * sin(radians_y)); 

    // Scale and translate (adjust values as needed)
    projected.x = projected.x * 50 + 500; // Scale and translate x
    projected.y = projected.y * 50 + 300; // Scale and translate y

    return projected;
}

void    my_mlx_pixel_put(t_data *data, int x, int y, int color) 
{     // // Isometric projection angles (30 degrees in radians)
    // double angle = M_PI / 6; // 30 degrees

    // // Isometric projection formula
    // projected.x = (int)((point.x - point.y) * cos(angle));
    // projected.y = (int)((point.x + point.y) * sin(angle) - point.z);
    char    *dst; 

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8)); 
    *(unsigned int*)dst = color; 
} 

void bresenham_line(t_data *img, t_point2d start, t_point2d end, int color) {
    int dx = abs(end.x - start.x);
    int dy = abs(end.y - start.y);

    int sx = (start.x < end.x) ? 1 : -1;
    int sy = (start.y < end.y) ? 1 : -1;

    int err = dx - dy;

    while (1) {
        // Plot the current pixel
        my_mlx_pixel_put(img, start.x, start.y, color);

        // Check if we've reached the endpoint
        if (start.x == end.x && start.y == end.y)
            break;

        int e2 = 2 * err;

        // Adjust the error and move in the x direction
        if (e2 > -dy) {
            err -= dy;
            start.x += sx;
        }

        // Adjust the error and move in the y direction
        if (e2 < dx) {
            err += dx;
            start.y += sy;
        }
    }
}

int main(void) 
{
    t_point3d points[] = {
        {0, 0, 0}, {1, 0, 0}, {2, 0, 0}, {3, 0, 0}, {4, 0, 0},
        {0, 1, 0}, {1, 1, 0}, {2, 1, 0}, {3, 1, 0}, {4, 1, 0},
        {0, 2, 0}, {1, 2, 0}, {2, 2, 1}, {3, 2, 0}, {4, 2, 0},
        {0, 3, 0}, {1, 3, 0}, {2, 3, 0}, {3, 3, 0}, {4, 3, 0},
        {0, 4, 0}, {1, 4, 0}, {2, 4, 0}, {3, 4, 0}, {4, 4, 0}
        // Add more points for a more complex shape
    };

    int num_points = sizeof(points) / sizeof(points[0]);

    void    *mlx; 
    void    *mlx_win; 
    t_data  img; 

    mlx = mlx_init(); 
    mlx_win = mlx_new_window(mlx, 1920, 1080, "Isometric View"); 
    img.img = mlx_new_image(mlx, 1920, 1080); 
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, 
                                &img.endian); 
    for (int i = 0; i < num_points; i++) {
        t_point2d projected = isometric_projection(points[i]);
        my_mlx_pixel_put(&img, projected.x, projected.y, 0x00FF0000); 
    }
    for (int i = 0; i < num_points; i++) {
        t_point3d point3d_start = points[i];

        // Example: Connect to the point to the right (if it exists)
        if ((i + 1) % 5 != 0) { // Prevent wrapping to next row
            t_point3d point3d_end = points[i + 1];
            t_point2d start = isometric_projection(point3d_start);
            t_point2d end = isometric_projection(point3d_end);
            bresenham_line(&img, start, end, 0x00FF0000); // Red color
        }

        // Example: Connect to the point below (if it exists)
        if (i + 5 < num_points) { // Check if a point below exists
            t_point3d point3d_end = points[i + 5];
            t_point2d start = isometric_projection(point3d_start);
            t_point2d end = isometric_projection(point3d_end);
            bresenham_line(&img, start, end, 0x00FF0000); // Red color
        }
    }
    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0); 
    mlx_loop(mlx); 
}