#include "fdf.h"

int 	ft_min_value(int value1, int value2, int value3)
{
	int min;
	
	if (value1 <= value2)
	{
		if (value1 <= value3)
			min = value1;
		else
			min = value3;
	}
	else
	{
		if (value2 <= value3)
			min = value2;
		else
			min = value3;
	}
	return (min);
}

int 	ft_max_value(int value1, int value2, int value3)
{
	int max;
	
	if (value1 >= value2)
	{
		if (value1 >= value3)
			max = value1;
		else
			max = value3;
	}
	else
	{
		if (value2 >= value3)
			max = value2;
		else
			max = value3;
	}
	return (max);
}

int 	ft_same_sign(int first, int second, int third)
{
	if ((first >= 0 && second >= 0 && third >= 0) ||
	(first < 0 && second < 0 && third < 0))
		return (1);
	return (0);
}

void	ft_fill_triangle(void *mlx_ptr, void *win_ptr, int x1, int y1, int x2, int y2, int x3, int y3, int color)
{
	int	min_x;
	int	min_y;
	int	max_x;
	int	max_y;
	
	min_x = ft_min_value(x1, x2, x3);
	min_y = ft_min_value(y1, y2, y3);
	max_x = ft_max_value(x1, x2, x3);
	max_y = ft_max_value(y1, y2, y3);
	
	int x;
	int y;
	
	y = min_y;
	while (y <= max_y)
	{
		x = min_x;
		while (x <= max_x)
		{
			if ((x == x1 && y == y1) || (x == x2 && y == y2) || (x == x3 && y == y3) ||
			ft_same_sign((x1 - x) * (y2 - y1) - (x2 - x1) * (y1 - y),
			(x2 - x) * (y3 - y2) - (x3 - x2) * (y2 - y),
			(x3 - x) * (y1 - y3) - (x1 - x3) * (y3 - y)))
				mlx_pixel_put(mlx_ptr, win_ptr, x, y, color);
			x++;
		}
		printf("\n");
		y++;
	}
}

void	ft_fill_quadrilateral(void *mlx_ptr, void *win_ptr, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int color)
{
	ft_fill_triangle(mlx_ptr, win_ptr, x1, y1, x3, y3, x4, y4, color);
	ft_fill_triangle(mlx_ptr, win_ptr, x1, y1, x2, y2, x4, y4, color);
}
//
//int 	main(void)
//{
//	ft_fill_quadrilateral(8, 0, 25, 4, 0, 20, 34, 28, 0x0000FF);
//	return (0);
//}