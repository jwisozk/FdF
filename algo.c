#include "fdf.h"

static void ft_return_position(t_param *p)
{
    int     i;
    int     j;

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

static void ft_move(t_param *p)
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

static void    ft_draw_lines(t_param *p)
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

static void ft_rotate_min(t_param *p, int i, int j)
{
    float x;
    float y;
    float z;

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

static void	ft_rotate(t_param* p)
{
    int     i;
    int     j;

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

static void ft_add_coords(t_param *p)
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

static void ft_equ_angle(t_param *p, int x, int y, int z)
{
    p->angle_x = x;
    p->angle_y = y;
    p->angle_z = z;
}


static void ft_scale(t_param *p, float scale)
{
    int     i;
    int     j;

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

static void	ft_perspective(t_param *p, int near)
{
    int i;
    int j;
    int z;

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

static void	ft_non_perspective(t_param *p)
{
    int i;
    int j;

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

static void ft_one_key(t_param *p, int x, int y, int z)
{
    mlx_clear_window(p->mlx_ptr, p->win_ptr);
    ft_equ_angle(p, x, y, z);
    ft_rotate(p);
}

static void ft_standart_key(t_param *p)
{
    mlx_clear_window(p->mlx_ptr, p->win_ptr);
    ft_add_coords(p);
}

static void ft_persp_key(t_param *p)
{
    mlx_clear_window(p->mlx_ptr, p->win_ptr);
    if (p->is_perspective == 0)
    {
        ft_perspective(p, -2000);
        p->is_perspective = 1;
    }
    else
    {
        p->is_perspective = 0;
        ft_non_perspective(p);
    }
}

static void ft_iso_key(t_param *p)
{
    mlx_clear_window(p->mlx_ptr, p->win_ptr);
    ft_add_coords(p);
    ft_equ_angle(p, 0, 0, -45);
    ft_rotate(p);
    ft_equ_angle(p, 60, 0, 0);
    ft_rotate(p);
}

static void ft_switch_color(t_param *p)
{
    mlx_clear_window(p->mlx_ptr, p->win_ptr);
    p->fillcolor = rand() % 16777216;
}

static void ft_fill_color(t_param *p)
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

static void ft_key_numbers(int keycode, void *param)
{
    t_param *p;

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

static int ft_key_press(int keycode, void *param)
{
    t_param *p;

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

static int ft_mouse_press(int button, int x, int y, void *param)
{
    t_param *p;
    int     scale;

    x = x + y;
    p = (t_param*)param;
    scale = abs((int)p->arr_lst[0][p->len_x - 1].x - (int)p->arr_lst[0][0].x);
    mlx_clear_window(p->mlx_ptr, p->win_ptr);
    if (button == 1)
        p->press_mouse_l = 1;
    if (button == 2)
        p->press_mouse_r = 1;
    if (button == 5 && scale < LIMIT_SCALE_UP)
        ft_scale(p, 1.1);
    if (button == 4 && scale > LIMIT_SCALE_DOWN)
        ft_scale(p, 0.9);
    ft_draw_lines(p);
    return (0);
}

static int ft_mouse_release(int button, int x, int y, void *param)
{
    t_param *p;

    x = x + y;
    p = (t_param*)param;
    if (button == 1)
        p->press_mouse_l = 0;
    if (button == 2)
        p->press_mouse_r = 0;
    return (0);
}

static void    ft_mouse_mini(t_param *p, int x, int y)
{
    if (y == 0)
        p->init_x = x;
    else
        p->init_y = y;
    ft_equ_angle(p, x, y, 0);
    ft_rotate(p);
}

static int ft_mouse_move(int x, int y, void *param)
{
    t_param *p;

    p = (t_param*)param;
    if (p->press_mouse_l == 1)
    {
        if (p->init_x == 0)
            p->init_x = x;
        if (p->init_y == 0)
            p->init_y = y;
        if (p->is_perspective == 1)
            ft_non_perspective(p);
        if (p->init_y > y + 10)
            ft_mouse_mini(p, 2, 0);
        if (p->init_y < y - 10)
            ft_mouse_mini(p, -2, 0);
        if (p->init_x > x + 10)
            ft_mouse_mini(p, 0, -2);
        if (p->init_x < x - 10)
            ft_mouse_mini(p, 0, 2);
        if (p->is_perspective == 1)
            ft_perspective(p, -2000);
        mlx_clear_window(p->mlx_ptr, p->win_ptr);
        ft_draw_lines(p);
    }
    return (0);
}

static int ft_close_window(void *param)
{
    t_param *p;

    p = (t_param*)param;
    ft_free_all((void**)p->arr_lst, p->len_y);
    exit(0);
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