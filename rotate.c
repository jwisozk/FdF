/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twill <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 21:55:17 by twill             #+#    #+#             */
/*   Updated: 2019/06/30 21:55:18 by twill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_rotate_min(t_param *p, int i, int j)
{
	float	x;
	float	y;
	float	z;

	x = p->arr_lst[i][j].x;
	y = p->arr_lst[i][j].y;
	z = p->arr_lst[i][j].z;
	if (p->angle_x)
	{
		p->arr_lst[i][j].y = y * COS(p->angle_x) - z * SIN(p->angle_x);
		p->arr_lst[i][j].z = y * SIN(p->angle_x) + z * COS(p->angle_x);
	}
	if (p->angle_y)
	{
		p->arr_lst[i][j].x = x * COS(p->angle_y) + z * SIN(p->angle_y);
		p->arr_lst[i][j].z = z * COS(p->angle_y) - x * SIN(p->angle_y);
	}
	if (p->angle_z)
	{
		p->arr_lst[i][j].x = x * COS(p->angle_z) - y * SIN(p->angle_z);
		p->arr_lst[i][j].y = x * SIN(p->angle_z) + y * COS(p->angle_z);
	}
}

void		ft_rotate(t_param *p)
{
	int	i;
	int	j;

	i = 0;
	while (i < p->len_y)
	{
		j = 0;
		while (j < p->len_x)
		{
			ft_rotate_min(p, i, j);
			j++;
		}
		i++;
	}
}

void		ft_equ_angle(t_param *p, int x, int y, int z)
{
	p->angle_x = x;
	p->angle_y = y;
	p->angle_z = z;
}
