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

static int		ft_sign(float first, float second, float third)
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

static int		ft_whether_point_inside_triangle(t_param *p, t_point *point,
                                                   int i, int j, int x)
{
    if ((x == p->arr_lst[i][j].x && p->var2 == p->arr_lst[i][j].y) ||
        (x == point->x && p->var2 == point->y) ||
        (x == p->arr_lst[i + 1][j + 1].x &&	p->var2 == p->arr_lst[i + 1][j + 1].y)
        || ft_sign((p->arr_lst[i][j].x - x) * (point->y - p->arr_lst[i][j].y) -
                   (point->x - p->arr_lst[i][j].x) * (p->arr_lst[i][j].y - p->var2),
                   (point->x - x) * (p->arr_lst[i + 1][j + 1].y - point->y) -
                   (p->arr_lst[i + 1][j + 1].x - point->x) * (point->y - p->var2),
                   (p->arr_lst[i + 1][j + 1].x - x) * (p->arr_lst[i][j].y -
                                                       p->arr_lst[i + 1][j + 1].y) - (p->arr_lst[i][j].x -
                                                                                      p->arr_lst[i + 1][j + 1].x) * (p->arr_lst[i + 1][j + 1].y - p->var2)))
        return (1);
    return (0);
}

static void		ft_fill_triangle(t_param *p, int i, int j, int v)
{
    t_point	*point;
    int 	x;

    ft_set_var_to_zero(p);
    point = v ? &(p->arr_lst[i][j + 1]) : &(p->arr_lst[i + 1][j]);
    p->var1 = ft_min(p->arr_lst[i][j].x, point->x, p->arr_lst[i + 1][j + 1].x);
    p->var2 = ft_min(p->arr_lst[i][j].y, point->y, p->arr_lst[i + 1][j + 1].y);
    p->var3 = ft_max(p->arr_lst[i][j].x, point->x, p->arr_lst[i + 1][j + 1].x);
    p->var4 = ft_max(p->arr_lst[i][j].y, point->y, p->arr_lst[i + 1][j + 1].y);
    while (p->var2 <= p->var4)
    {
        x = p->var1;
        while (x <= p->var3)
        {
            if (ft_whether_point_inside_triangle(p, point, i, j, x))
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