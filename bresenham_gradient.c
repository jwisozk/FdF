#include "fdf.h"

static unsigned int	ft_pack_color(unsigned char a, unsigned char r,
					unsigned char g, unsigned char b)
{
	return ((a << 24) + (r << 16) + (g << 8) + b);
}


static int			max_delta(int delta_a, int delta_r, int delta_g, int delta_b)
{
	if (delta_a >= delta_r && delta_a >= delta_g && delta_a >= delta_b)
		return (delta_a);
	if (delta_r >= delta_a && delta_r >= delta_g && delta_r >= delta_b)
		return (delta_r);
	if (delta_g >= delta_a && delta_g >= delta_r && delta_r >= delta_b)
		return (delta_r);
	return (delta_b);
}

static void			ft_unpack_color(unsigned int color, t_color_params *c, int flag)
{
	if (flag == 1)
	{
		c->a1 = (color >> 24) & 255;
		c->r1 = (color >> 16) & 255;
		c->g1 = (color >> 8) & 255;
		c->b1 = color & 255;
	}
	if (flag == 2)
	{
		c->a2 = (color >> 24) & 255;
		c->r2 = (color >> 16) & 255;
		c->g2 = (color >> 8) & 255;
		c->b2 = color & 255;
	}
}

static int			ft_gradient_step(unsigned int *color1, unsigned int *color2,
					int gradient_length)
{
	t_color_params	c;
	ft_unpack_color(*color1, &c, 1);
	ft_unpack_color(*color2, &c, 2);
    c.delta_a = c.a2 - c.a1;
	c.delta_r = c.r2 - c.r1;
	c.delta_g = c.g2 - c.g1;
	c.delta_b = c.b2 - c.b1;
    c.m_delta = max_delta(abs(c.delta_a), abs(c.delta_r), abs(c.delta_g),
	abs(c.delta_b));
    if (!(c.m_delta))
        c.m_delta = 1;
    if (!gradient_length)
        gradient_length = 1;
    c.step = gradient_length > c.m_delta ? gradient_length / c.m_delta :
	c.m_delta / gradient_length;
    if (!c.step || !(gradient_length / c.step))
        c.step = 1;
	c.delta_a = c.delta_a / (gradient_length / c.step);
	c.delta_r = c.delta_r / (gradient_length / c.step);
	c.delta_g = c.delta_g / (gradient_length / c.step);
	c.delta_b = c.delta_b / (gradient_length / c.step);
	*color1 = ft_pack_color(c.a1 + c.delta_a, c.r1 + c.delta_r, c.g1 +
	c.delta_g, c.b1 + c.delta_b);
    return (c.step);
}

static int			ft_h_or_v(t_param *p, int i, int j, t_point *point)
{
	return ((abs((int)point->y - (int)p->arr_lst[i][j].y) <
	abs((int)point->x - (int)p->arr_lst[i][j].x)) ? 1 : 0);
}

static void			ft_assign_values(t_param* p, int i, int j, t_point *point)
{
	int dx;
	int dy;
	
	dx = point->x - p->arr_lst[i][j].x;
	dy = point->y - p->arr_lst[i][j].y;
	if (p->var10)
	{
		p->var11 = dx >= 0 ? point->x : p->arr_lst[i][j].x;
		p->var1 = dx >= 0 ? dx : p->arr_lst[i][j].x - point->x;
		p->var2 = dx >= 0 ? dy : p->arr_lst[i][j].y - point->y;
		p->var3 = dx >= 0 ? p->arr_lst[i][j].x : point->x;
		p->var4 = dx >= 0 ? p->arr_lst[i][j].y : point->y;
	}
	else
	{
		p->var11 = dy >= 0 ? point->y : p->arr_lst[i][j].y;
		p->var1 = dy >= 0 ? dy : p->arr_lst[i][j].y - point->y;
		p->var2 = dy >= 0 ? dx : p->arr_lst[i][j].x - point->x;
		p->var3 = dy >= 0 ? p->arr_lst[i][j].y : point->y;
		p->var4 = dy >= 0 ? p->arr_lst[i][j].x : point->x;
	}
	p->var6 = (unsigned int)p->arr_lst[i][j].color;
	p->var7 = (unsigned int)point->color;
	p->var9 = 1;
	p->var9 = p->var2 < 0 ? -1 : p->var9;
}

//	int var1;		// dx || dy
//	int var2;		// dy || dx
//	int var3;		// x || y
//	int var4;		// y || x
//	int var5;		// shift (step)
//	int var6;		// color1
//	int var7;		// color2
//	int var8;		// slope
//	int var9;		// yi || xi
//	int var10;		// var10 == 1 - hor. line; var == 0 - ver. line
//	int var11;		// x2 || y2
//	int	var12;		// var12 = 0 - color1 == color2; var12 = 1 - color1 != color2

void				ft_bresenham(t_param *p, int i, int j, int v)
{
	ft_set_var_to_zero(p);
	p->point = &(p->arr_lst[v ? i + 1 : i][v ? j : j + 1]);
	p->var10 = ft_h_or_v(p, i, j, p->point);
	ft_assign_values(p, i, j, p->point);
	p->var2 = p->var2 < 0 ? -(p->var2) : p->var2;
	p->var8 = 2 * p->var2 - p->var1;
	p->var12 = p->arr_lst[i][j].color != p->point->color ? 1 : 0;
	if (p->var12)
		p->var5 = ft_gradient_step(&(p->var6), &(p->var7), p->var11 - p->var3);
	while (p->var3 < p->var11)
	{
		mlx_pixel_put(p->mlx_ptr, p->win_ptr, (p->var10 ? p->var3 : p->var4),
		(p->var10 ? p->var4 : p->var3), p->var6);
		p->var4 = p->var8 >= 0 ? p->var4 + p->var9 : p->var4;
		p->var8 = p->var8 >= 0 ? p->var8 - 2 * p->var1 : p->var8;
		p->var8 = p->var8 + 2 * p->var2;
		p->var5 = p->var12 ? p->var5 - 1 : p->var5;
		if (p->var12)
			p->var5 = p->var5 ? p->var5 : ft_gradient_step(&(p->var6),
			&(p->var7),	p->var11 - p->var3);
		(p->var3)++;
	}
	mlx_pixel_put(p->mlx_ptr, p->win_ptr, (p->var10 ? p->var3 : p->var4),
	(p->var10 ? p->var4 : p->var3), p->var6);
}