/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twill <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 20:58:16 by twill             #+#    #+#             */
/*   Updated: 2019/06/30 20:58:17 by twill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_fill_color(t_param *p)
{
	mlx_clear_window(p->mlx_ptr, p->win_ptr);
	if (p->is_fillcolor == 0)
	{
		p->is_fillcolor = 1;
		p->fillcolor = 0;
	}
	else
	{
		p->is_fillcolor = 0;
		p->fillcolor = 0;
	}
}

void	ft_key_numbers(int keycode, void *param)
{
	t_param	*p;

	p = (t_param*)param;
	if (keycode == 18)
		ft_standart_key(p);
	if (keycode == 19)
		ft_iso_key(p);
	if (keycode == 20)
		ft_persp_key(p);
	if (keycode == 21)
		ft_fill_color(p);
	if (keycode == 23)
		ft_switch_color(p);
}

int		ft_key_press(int keycode, void *param)
{
	t_param	*p;

	p = (t_param*)param;
	if (keycode == 53)
		ft_close_window(p);
	if (keycode == 0)
		ft_one_key(p, 0, 0, -2);
	if (keycode == 2)
		ft_one_key(p, 0, 0, 2);
	if (keycode == 13)
		ft_one_key(p, 2, 0, 0);
	if (keycode == 1)
		ft_one_key(p, -2, 0, 0);
	if (keycode == 12)
		ft_one_key(p, 0, -2, 0);
	if (keycode == 14)
		ft_one_key(p, 0, 2, 0);
	ft_key_numbers(keycode, p);
	ft_draw_lines(p);
	return (0);
}
