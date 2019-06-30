/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twill <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 20:05:55 by twill             #+#    #+#             */
/*   Updated: 2019/06/30 20:05:57 by twill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_is_same_sign(float first, float second, float third)
{
	if ((first >= 0.0 && second >= 0.0 && third >= 0.0) ||
		(first < 0.0 && second < 0.0 && third < 0.0))
		return (1);
	return (0);
}

void	ft_set_var_to_zero(t_param *p)
{
	p->var1 = 0;
	p->var2 = 0;
	p->var3 = 0;
	p->var4 = 0;
	p->var5 = 0;
	p->var6 = 0;
	p->var7 = 0;
	p->var8 = 0;
	p->var9 = 0;
	p->var10 = 0;
}

int		ft_print_error(char *str)
{
	ft_putstr(str);
	ft_putchar('\n');
	exit(0);
}

int		ft_getlen_x(char **arr)
{
	int len;

	len = 0;
	while (arr[len] != NULL)
		len++;
	return (len);
}

void	ft_init_param(t_param *p, int len_y)
{
	p->len_y = len_y;
	p->press_mouse_l = 0;
	p->is_fillcolor = 0;
	p->init_x = 0;
	p->init_y = 0;
	p->init_z = 0;
	p->angle_x = 0;
	p->angle_y = 0;
	p->angle_z = 0;
	p->move_x = 0;
	p->move_y = 0;
	p->move_z = 0;
	p->fillcolor = DEFAULT_COLOR;
	p->is_perspective = 0;
}
