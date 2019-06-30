/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twill <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 21:47:24 by twill             #+#    #+#             */
/*   Updated: 2019/06/30 21:47:25 by twill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_return_position(t_param *p)
{
	int	i;
	int	j;

	i = 0;
	while (i < p->len_y)
	{
		j = 0;
		while (j < p->len_x)
		{
			p->arr_lst[i][j].x = p->arr_lst[i][j].x_move;
			p->arr_lst[i][j].y = p->arr_lst[i][j].y_move;
			p->arr_lst[i][j].z = p->arr_lst[i][j].z_move;
			j++;
		}
		i++;
	}
}

void	ft_perspective(t_param *p, int near)
{
	int	i;
	int	j;
	int	z;

	i = 0;
	while (i < p->len_y)
	{
		j = 0;
		while (j < p->len_x)
		{
			z = p->arr_lst[i][j].z - 1000;
			p->arr_lst[i][j].x_p = p->arr_lst[i][j].x;
			p->arr_lst[i][j].y_p = p->arr_lst[i][j].y;
			p->arr_lst[i][j].z_p = p->arr_lst[i][j].z;
			if (z)
			{
				p->arr_lst[i][j].x = near * p->arr_lst[i][j].x / z / 2;
				p->arr_lst[i][j].y = near * p->arr_lst[i][j].y / z / 2;
				p->arr_lst[i][j].z = near / 2;
			}
			j++;
		}
		i++;
	}
}

void	ft_non_perspective(t_param *p)
{
	int	i;
	int	j;

	i = 0;
	while (i < p->len_y)
	{
		j = 0;
		while (j < p->len_x)
		{
			p->arr_lst[i][j].x = p->arr_lst[i][j].x_p;
			p->arr_lst[i][j].y = p->arr_lst[i][j].y_p;
			p->arr_lst[i][j].z = p->arr_lst[i][j].z_p;
			j++;
		}
		i++;
	}
}

void	ft_scale(t_param *p, float scale)
{
	int	i;
	int	j;

	i = 0;
	while (i < p->len_y)
	{
		j = 0;
		while (j < p->len_x)
		{
			p->arr_lst[i][j].x = p->arr_lst[i][j].x * scale;
			p->arr_lst[i][j].y = p->arr_lst[i][j].y * scale;
			p->arr_lst[i][j].z = p->arr_lst[i][j].z * scale;
			j++;
		}
		i++;
	}
}
