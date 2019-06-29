#include "fdf.h"

unsigned int	pack_color(unsigned char a, unsigned char r, unsigned char g, unsigned char b)
{
//	printf("result = %d, a = %d, r = %d, g = %d, b = %d\n", (a << 24) + (r << 16) + (g << 8) + b, a, r, g, b);
	return ((a << 24) + (r << 16) + (g << 8) + b);
}

void	unpack_color(unsigned int color, unsigned char *a, unsigned char *r, unsigned char *g, unsigned char *b)
{
//	printf("unpack_color(): &a = %p, &r = %p, &g = %p, &b = %p\n", a, r, g, b);
//	printf("unpack_color(): color = %d\n", color);
	*a = (color >> 24) & 255;
	*r = (color >> 16) & 255;
	*g = (color >> 8) & 255;
	*b = color & 255;
//	printf("unpack_color(): r = %d\n", *r);
}

int max_delta(int delta_a, int delta_r, int delta_g, int delta_b)
{
	if (delta_a >= delta_r && delta_a >= delta_g && delta_a >= delta_b)
		return (delta_a);
	if (delta_r >= delta_a && delta_r >= delta_g && delta_r >= delta_b)
		return (delta_r);
	if (delta_g >= delta_a && delta_g >= delta_r && delta_r >= delta_b)
		return (delta_r);
	return (delta_b);
}

int	gradient_step(unsigned int *color1, unsigned int *color2, int gradient_length)
{
	unsigned char a1;
	unsigned char r1;
	unsigned char g1;
	unsigned char b1;
	unsigned char a2;
	unsigned char r2;
	unsigned char g2;
	unsigned char b2;
	int shift;
	int m_delta;
//	printf("gradient_step(): &a1 = %p, &r1 = %p, &g1 = %p, &b1 = %p\n", &a1, &r1, &g1, &b1);
//	printf("gradient_step(): &a2 = %p, &r2 = %p, &g2 = %p, &b2 = %p\n", &a2, &r2, &g2, &b2);
//	printf("gradient_step(): color = %d\n", color1);
	unpack_color(*color1, &a1, &r1, &g1, &b1);
	unpack_color(*color2, &a2, &r2, &g2, &b2);
    int delta_a = a2 - a1;
	int delta_r = r2 - r1;
//	printf("r2 = %d, r1 = %d, delta_r = %d\n", r2, r1, delta_r);
	int delta_g = g2 - g1;
	int delta_b = b2 - b1;
//    printf("delta_a = %d, delta_r = %d, delta_g = %d, delta_b = %d\n", delta_a, delta_r, delta_g, delta_b);
    // ADD abs()
    m_delta = max_delta(abs(delta_a), abs(delta_r), abs(delta_g), abs(delta_b));
    if (!m_delta)
        m_delta = 1;
    if (!gradient_length)
        gradient_length = 1;
//    printf("\tm_delta = %d, gradient_length = %d\n", m_delta, gradient_length);
    shift = gradient_length > m_delta ? gradient_length / m_delta : m_delta / gradient_length;
    if (!shift)
        shift = 1;
//    printf("gradient_step(): gradient_length = %d, m_delta / gradient_length = %d\n", gradient_length, m_delta / gradient_length);
	delta_a = delta_a / (gradient_length / shift);
	delta_r = delta_r / (gradient_length / shift);
	delta_g = delta_g / (gradient_length / shift);
	delta_b = delta_b / (gradient_length / shift);
	// ???
	*color1 = pack_color(a1 + delta_a, r1 + delta_r, g1 + delta_g, b1 + delta_b);
    return (shift);
}

static void ft_bresenham_hor_gradient(int x1, int y1, int x2, int y2, void *mlx_ptr, void *win_ptr, unsigned int color1, unsigned int color2)
{
	int dx;
	int dy;
	int x;
	int y;
	int slope;
	int yi;
	int shift;
	
	dx = x2 - x1;
	dy = y2 - y1;
	yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	slope = 2 * dy - dx;
	x = x1;
	y = y1;
    shift = gradient_step(&color1, &color2, x2 - x);
    while (x < x2)
	{
		mlx_pixel_put(mlx_ptr, win_ptr, x, y, color1);
		if (slope >= 0)
		{
			y = y + yi;
			slope -= 2 * dx;
		}
		slope += 2 * dy;
		shift--;
		if (!shift)
			shift = gradient_step(&color1, &color2, x2 - x);
		x++;
	}
	mlx_pixel_put(mlx_ptr, win_ptr, x, y, color1);
}

static void ft_bresenham_ver_gradient(int x1, int y1, int x2, int y2, void *mlx_ptr, void *win_ptr, unsigned int color1, unsigned int color2)
{
	int dx;
	int dy;
	int x;
	int y;
	int slope;
	int xi;
	int shift;
	
	dx = x2 - x1;
	dy = y2 - y1;
	xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	slope = 2 * dx - dy;
	x = x1;
	y = y1;
	shift = gradient_step(&color1, &color2, y2 - y);
	while (y < y2)
	{
		mlx_pixel_put(mlx_ptr, win_ptr, x, y, color1);
		if (slope >= 0)
		{
			x = x + xi;
			slope -= 2 * dy;
		}
		slope += 2 * dx;
		shift--;
		if (!shift)
			shift = gradient_step(&color1, &color2, y2 - y);
		y++;
	}
	mlx_pixel_put(mlx_ptr, win_ptr, x, y, color1);
}

void ft_bresenham_gradient(void *mlx_ptr, void *win_ptr, int x1, int y1, int x2, int y2, unsigned int color1, unsigned int color2)
{
    if (abs(y2 - y1) < abs(x2 - x1))
	{
		if (x1 < x2)
			ft_bresenham_hor_gradient(x1, y1, x2, y2, mlx_ptr, win_ptr, color1, color2);
		else
			ft_bresenham_hor_gradient(x2, y2, x1, y1, mlx_ptr, win_ptr, color1, color2);
	}
	else
	{
		if (y1 < y2)
			ft_bresenham_ver_gradient(x1, y1, x2, y2, mlx_ptr, win_ptr, color1, color2);
		else
			ft_bresenham_ver_gradient(x2, y2, x1, y1, mlx_ptr, win_ptr, color1, color2);
	}
}
