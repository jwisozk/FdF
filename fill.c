/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twill <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 20:07:28 by twill             #+#    #+#             */
/*   Updated: 2019/06/30 20:07:31 by twill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static float	ft_min(float value1, float value2, float value3)
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

static float	ft_max(float value1, float value2, float value3)
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

static int		ft_is_pnt_inside_triangle(t_param *p, int i, int j, int x)
{
	if ((x == p->arr_lst[i][j].x && p->var2 == p->arr_lst[i][j].y) ||
		(x == p->pnt->x && p->var2 == p->pnt->y) ||
		(x == p->arr_lst[i + 1][j + 1].x && p->var2 ==
		p->arr_lst[i + 1][j + 1].y) || ft_is_same_sign((p->arr_lst[i][j].x - x)
		* (p->pnt->y - p->arr_lst[i][j].y) - (p->pnt->x - p->arr_lst[i][j].x) *
		(p->arr_lst[i][j].y - p->var2), (p->pnt->x - x) *
		(p->arr_lst[i + 1][j + 1].y - p->pnt->y) -
		(p->arr_lst[i + 1][j + 1].x - p->pnt->x) * (p->pnt->y - p->var2),
		(p->arr_lst[i + 1][j + 1].x - x) * (p->arr_lst[i][j].y -
		p->arr_lst[i + 1][j + 1].y) - (p->arr_lst[i][j].x -
		p->arr_lst[i + 1][j + 1].x) * (p->arr_lst[i + 1][j + 1].y - p->var2)))
		return (1);
	return (0);
}

static void		ft_fill_triangle(t_param *p, int i, int j, int v)
{
	int		x;

	ft_set_var_to_zero(p);
	p->pnt = v ? &(p->arr_lst[i][j + 1]) : &(p->arr_lst[i + 1][j]);
	p->var1 = ft_min(p->arr_lst[i][j].x, p->pnt->x, p->arr_lst[i + 1][j + 1].x);
	p->var2 = ft_min(p->arr_lst[i][j].y, p->pnt->y, p->arr_lst[i + 1][j + 1].y);
	p->var3 = ft_max(p->arr_lst[i][j].x, p->pnt->x, p->arr_lst[i + 1][j + 1].x);
	p->var4 = ft_max(p->arr_lst[i][j].y, p->pnt->y, p->arr_lst[i + 1][j + 1].y);
	while (p->var2 <= p->var4)
	{
		x = p->var1;
		while (x <= p->var3)
		{
			if (ft_is_pnt_inside_triangle(p, i, j, x))
				mlx_pixel_put(p->mlx_ptr, p->win_ptr, x, p->var2, p->fillcolor);
			x++;
		}
		(p->var2)++;
	}
}

void			ft_fill_quadrilateral(t_param *p, int i, int j)
{
	ft_fill_triangle(p, i, j, 0);
	ft_fill_triangle(p, i, j, 1);
}
