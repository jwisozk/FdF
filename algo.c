#include "fdf.h"

void ft_move(t_param *p)
{
    int       i;
    int       j;

    i = 0;
    while (i < p->len_y)
    {
        j = 0;
        while (j < p->len_x)
        {
            p->arr_lst[i][j].x_move = p->arr_lst[i][j].x;
            p->arr_lst[i][j].y_move = p->arr_lst[i][j].y;
            p->arr_lst[i][j].z_move = p->arr_lst[i][j].z;
            p->arr_lst[i][j].x = p->arr_lst[i][j].x + DW / 2;
            p->arr_lst[i][j].y = p->arr_lst[i][j].y + DH / 2;
            j++;
        }
        i++;
    }
}

void    ft_draw_lines(t_param *p)
{
    int     i;
    int     j;

    i = 0;
    ft_move(p);
    while (i < p->len_y)
    {
        j = 0;
        while (j < p->len_x)
        {
            if (i + 1 < p->len_y && j + 1 < p->len_x && p->is_fillcolor)
              ft_fill_quadrilateral(p, i, j);
            if (j + 1 < p->len_x)
                ft_bresenham(p, i, j, 0);
            if (i + 1 < p->len_y)
                ft_bresenham(p, i, j, 1);
            j++;
        }
        i++;
    }
    ft_return_position(p);
}

 void ft_add_coords(t_param *p)
{
    int     i;
    int     j;
    int     d;

    d = DIST / p->len_y;
    i = 0;
    while (i < p->len_y)
    {
        j = 0;
        while (j < p->len_x)
        {
            p->arr_lst[i][j].x = (j == 0) ? 0 - p->len_x * d / 2 : p->arr_lst[i][j - 1].x + d;
            p->arr_lst[i][j].y = (i == 0) ? 0 - p->len_y * d / 2 : p->arr_lst[i - 1][j].y + d;
            p->arr_lst[i][j].z = p->arr_lst[i][j].z_init * d;
            j++;
        }
        i++;
    }
}

void    ft_open_window(t_param *p)
{
    void	*mlx_ptr;
    void	*win_ptr;

    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, DW, DH, "80s_team");
    p->mlx_ptr = mlx_ptr;
    p->win_ptr = win_ptr;
    ft_add_coords(p);
    ft_draw_lines(p);
    mlx_hook(win_ptr, 17, 0, ft_close_window, p);
    mlx_hook(win_ptr, 2, 0, ft_key_press, p);
    mlx_hook(win_ptr, 4, 0, ft_mouse_press, p);
    mlx_hook(win_ptr, 5, 0, ft_mouse_release, p);
    mlx_hook(win_ptr, 6, 0, ft_mouse_move, p);
    mlx_loop(mlx_ptr);
}