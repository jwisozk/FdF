/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twill <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 22:00:37 by twill             #+#    #+#             */
/*   Updated: 2019/06/30 22:00:42 by twill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_mouse_press(int button, int x, int y, void *param)
{
	t_param	*p;
	int		scale;

	x = x + y;
	p = (t_param*)param;
	scale = abs((int)p->arr_lst[0][p->len_x - 1].x - (int)p->arr_lst[0][0].x);
	mlx_clear_window(p->mlx_ptr, p->win_ptr);
	if (button == 1)
		p->press_mouse_l = 1;
	if (button == 5 && scale < LIMIT_SCALE_UP)
		ft_scale(p, 1.1);
	if (button == 4 && scale > LIMIT_SCALE_DOWN)
		ft_scale(p, 0.9);
	ft_draw_lines(p);
	return (0);
}

int		ft_mouse_release(int button, int x, int y, void *param)
{
	t_param *p;

	x = x + y;
	p = (t_param*)param;
	if (button == 1)
		p->press_mouse_l = 0;
	return (0);
}

void	ft_mouse_mini(t_param *p, int x, int y)
{
	if (p->init_y > y + 10)
	{
		p->init_y = y;
		ft_equ_angle(p, 2, 0, 0);
		ft_rotate(p);
	}
	if (p->init_y < y - 10)
	{
		p->init_y = y;
		ft_equ_angle(p, -2, 0, 0);
		ft_rotate(p);
	}
	if (p->init_x > x + 10)
	{
		p->init_x = x;
		ft_equ_angle(p, 0, -2, 0);
		ft_rotate(p);
	}
	if (p->init_x < x - 10)
	{
		p->init_x = x;
		ft_equ_angle(p, 0, 2, 0);
		ft_rotate(p);
	}
}

int		ft_mouse_move(int x, int y, void *param)
{
	t_param	*p;

	p = (t_param*)param;
	if (p->press_mouse_l == 1)
	{
		if (p->init_x == 0)
			p->init_x = x;
		if (p->init_y == 0)
			p->init_y = y;
		if (p->is_perspective == 1)
			ft_non_perspective(p);
		ft_mouse_mini(p, x, y);
		if (p->is_perspective == 1)
			ft_perspective(p, -2000);
		mlx_clear_window(p->mlx_ptr, p->win_ptr);
		ft_draw_lines(p);
	}
	return (0);
}

int		ft_close_window(void *param)
{
	t_param	*p;

	p = (t_param*)param;
	ft_free_all((void**)p->arr_lst, p->len_y);
	exit(0);
}
