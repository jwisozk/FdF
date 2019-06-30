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

static int		ft_is_same_sign(float first, float second, float third)
{
	if ((first >= 0.0 && second >= 0.0 && third >= 0.0) ||
		(first < 0.0 && second < 0.0 && third < 0.0))
		return (1);
	return (0);
}

void			ft_set_var_to_zero(t_param *p)
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
