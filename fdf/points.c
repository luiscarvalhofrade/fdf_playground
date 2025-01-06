#include "fdf.h"
#include <math.h>

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