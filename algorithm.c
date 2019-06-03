/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twill <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 20:53:50 by twill             #+#    #+#             */
/*   Updated: 2019/05/28 22:53:28 by twill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"

void	draw_bresenham_line(void *mlx_ptr, void *win_ptr,
		int x1,	int y1, int x2, int y2, int color)
{
	int dx;
	int dy;
	int	step;
	float	slope;
	float 	error;
	int	x;
	int	y;

	////
	mlx_ptr = 0;
	win_ptr = 0;
	color = 0;
	////

	dx = x2 - x1;
	dy = y2 - y1;
	slope = abs(dx) > abs(dy) ? abs(dy) / abs(dx) : abs(dx) / abs(dy);
	step = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	error = 0;
	x = x1;
	y = y1;
	while (step > 0)
	{
//		mlx_pixel_put(mlx_ptr, win_ptr, x1, y1, color);
//		printf("x = %d, y = %d, error = %f\n", x, y, error);
		error = error + slope;
		x = abs(dx) > abs(dy) ? x++ : (int)round((float)x + error);
		y = abs(dy) > abs(dx) ? y++ : (int)round((float)y + error);
		step--;
	}
}

void	draw_line(void *mlx_ptr, void *win_ptr, float x1, float y1,
		float x2, float y2,	int color)
{
	float	x, y, dx, dy, step;
	int		i;

	dx = x2 - x1;
	dy = y2 - y1;
	if (fabs(dx) >= fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	dx = dx / step;
	dy = dy / step;
	x = x1;
	y = y1;
	i = 0;
	while (i <= step)
	{
//		printf("x = %d, y = %d\n", (int)round(x), (int)round(y));
		mlx_pixel_put(mlx_ptr, win_ptr, x, y, color);
		x = x + dx;
		y = y + dy;
		i++;
	}
}
/*
void	ft_wire_designer(void *mlx_ptr, void *win_ptr,
		t_point arr[], int n, int color)
{
	int		i;

	i = 0;
	while (i + 1 < n)
	{
		draw_line(mlx_ptr, win_ptr, arr[i].x, arr[i].y,
		arr[i + 1].x, arr[i + 1].y, color);
		i++;
	}
	draw_line(mlx_ptr, win_ptr, arr[i].x, arr[i].y,
	arr[0].x, arr[0].y, color);
}
*/

void	ft_iso_modifier(void *mlx_ptr, void *win_ptr,
        t_point **arr_lst, int len_x, int len_y)
{
    int i;
    int j;
    int coef_x;
    int coef_y;

    coef_x = len_x;
    coef_y = 1;
    i = 0;
    printf("len_x = %d, len_y = %d\n\n", len_x, len_y);
    while (i < len_y)
    {
        j = 0;
        while (j < len_x && coef_y != len_y)
        {
            printf("i = %d, j = %d\n", (int)i, (int)j);
            if (j + 1 != len_x)
                draw_line(mlx_ptr, win_ptr,
                          arr_lst[i][j].x * H_DIST_BTWN_TWO_POINT,
                          arr_lst[i][j].y * H_DIST_BTWN_TWO_POINT + (coef_x - 1) * H_DIST_BTWN_TWO_POINT,
                          arr_lst[i][j + 1].x * H_DIST_BTWN_TWO_POINT,
                          arr_lst[i][j + 1].y * H_DIST_BTWN_TWO_POINT + (coef_x - 2) * H_DIST_BTWN_TWO_POINT,
                          0xFFFFFF);
            if (i + 1 != len_y)
                draw_line(mlx_ptr, win_ptr,
                          arr_lst[i][j].x * V_DIST_BTWN_TWO_POINT,
                          arr_lst[i][j].y * V_DIST_BTWN_TWO_POINT + (coef_x - 1) * H_DIST_BTWN_TWO_POINT,
                          arr_lst[i + 1][j].x * V_DIST_BTWN_TWO_POINT,
                          arr_lst[i + 1][j].y * V_DIST_BTWN_TWO_POINT + (coef_x - 2) * H_DIST_BTWN_TWO_POINT,
                          0xFFFFFF);
            coef_x--;
            j++;
        }
        i++;
    }
}

void    ft_wire_designer(void *mlx_ptr, void *win_ptr,
        t_point **arr_lst, int len_x, int len_y)
{
    int i;
    int j;

    i = 0;
    printf("len_x = %d, len_y = %d\n\n", len_x, len_y);
    while (i < len_y)
    {
        j = 0;
        while (j < len_x)
        {
            printf("i = %d, j = %d\n", (int)i, (int)j);
            if (j + 1 != len_x)
            draw_line(mlx_ptr, win_ptr,
            arr_lst[i][j].x * H_DIST_BTWN_TWO_POINT,
            arr_lst[i][j].y * H_DIST_BTWN_TWO_POINT,
            arr_lst[i][j + 1].x * H_DIST_BTWN_TWO_POINT,
            arr_lst[i][j + 1].y * H_DIST_BTWN_TWO_POINT,
            0xFFFFFF);
            if (i + 1 != len_y)
            draw_line(mlx_ptr, win_ptr,
            arr_lst[i][j].x * V_DIST_BTWN_TWO_POINT,
            arr_lst[i][j].y * V_DIST_BTWN_TWO_POINT,
            arr_lst[i + 1][j].x * V_DIST_BTWN_TWO_POINT,
            arr_lst[i + 1][j].y * V_DIST_BTWN_TWO_POINT,
            0xFFFFFF);
            j++;
        }
        i++;
    }
}

void    ft_open_new_window(t_point **arr_lst, int len_x, int len_y)
{
    void	*mlx_ptr;
    void	*win_ptr;

    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, 1600, 900, "80s_team");
    ft_iso_modifier(mlx_ptr, win_ptr, arr_lst, len_x, len_y);
    mlx_loop(mlx_ptr);
}
/*
int		deal_key(int key, void *param)
{
	key = 1;
	param = (void *)"a";
	ft_putchar('X');
	return (0);
}
*/
/*
int		main()
{
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 100, 100, "80s_team");
//	draw_line(mlx_ptr, win_ptr, 9.8, 10.1, 16.1, 2.3, 0xFFFFFF);
	draw_bresenham_line(mlx_ptr, win_ptr, 1, 1, 8, 4, 0xFF0000);

//////////
	t_point point1;
	t_point point2;
	t_point point3;
	
	point1.x = 20;
	point1.y = 20;
	point1.z = 0;
	point1.color = 0xFF0000;

	point2.x = 40;
	point2.y = 20;
	point2.z = 0;
	point2.color = 0x00FF00;

	point3.x = 40;
	point3.y = 40;
	point3.z = 0;
	point3.color = 0x0000FF;

	t_point arr[] = {point1, point2, point3};

	int whatever = arr[0].x;
	whatever = -1;

	ft_wire_designer(mlx_ptr, win_ptr, arr, 3, 0xFFFF00);
//////////

	mlx_key_hook(win_ptr, deal_key, (void *)0);
	mlx_loop(mlx_ptr);
	return (0);
}
*/