/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twill <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 20:58:16 by twill             #+#    #+#             */
/*   Updated: 2019/06/30 20:58:17 by twill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_one_key(t_param *p, int x, int y, int z)
{
	mlx_clear_window(p->mlx_ptr, p->win_ptr);
	ft_equ_angle(p, x, y, z);
	ft_rotate(p);
}

void	ft_standart_key(t_param *p)
{
	mlx_clear_window(p->mlx_ptr, p->win_ptr);
	ft_add_coords(p);
}

void	ft_persp_key(t_param *p)
{
	mlx_clear_window(p->mlx_ptr, p->win_ptr);
	if (p->is_perspective == 0)
	{
	    printf("z = %i, max_z = %i\n", (int)p->arr_lst[0][0].z, p->max_z * DIST / p->len_y);
		ft_perspective(p, -2000 + abs(p->max_z * DIST / p->len_y));
		p->is_perspective = 1;
	}
	else
	{
		p->is_perspective = 0;
		ft_non_perspective(p);
	}
}

void	ft_iso_key(t_param *p)
{
	mlx_clear_window(p->mlx_ptr, p->win_ptr);
	ft_add_coords(p);
	ft_equ_angle(p, 0, 0, -45);
	ft_rotate(p);
	ft_equ_angle(p, 60, 0, 0);
	ft_rotate(p);
}

void	ft_switch_color(t_param *p)
{
	mlx_clear_window(p->mlx_ptr, p->win_ptr);
	p->fillcolor = rand() % 16777216;
}
