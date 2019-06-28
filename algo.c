#include "fdf.h"

void ft_bresenham_hor(int x1, int y1, int x2, int y2, void *mlx_ptr, void *win_ptr, int color)
{
    int dx;
    int dy;
    int x;
    int y;
    int slope;
    int yi;

    dx = x2 - x1;
    dy = y2 - y1;
    yi = 1;
    if (dy < 0)
    {
        yi = -1;
        dy = -dy;
    }
    slope = 2 * dy - dx;
    x = x1;
    y = y1;
    while (x <= x2)
    {
        mlx_pixel_put(mlx_ptr, win_ptr, x, y, color);
        if (slope > 0)
        {
            y = y + yi;
            slope -= 2 * dx;
        }
        slope += 2 * dy;
        x++;
    }
}

void ft_bresenham_ver(int x1, int y1, int x2, int y2, void *mlx_ptr, void *win_ptr, int color)
{
    int dx;
    int dy;
    int x;
    int y;
    int slope;
    int xi;
    
    dx = x2 - x1;
    dy = y2 - y1;
    xi = 1;
    if (dx < 0)
    {
        xi = -1;
        dx = -dx;
    }
    slope = 2 * dx - dy;
    x = x1;
    y = y1;
    while (y <= y2)
    {
        mlx_pixel_put(mlx_ptr, win_ptr, x, y, color);
        if (slope > 0)
        {
            x = x + xi;
            slope -= 2 * dy;
        }
        slope += 2 * dx;
        y++;
    }
}

void ft_bresenham(int x1, int y1, int x2, int y2, void *mlx_ptr, void *win_ptr, int color)
{
    if (abs(y2 - y1) < abs(x2 - x1))
    {
        if (x1 < x2)
            ft_bresenham_hor(x1, y1, x2, y2, mlx_ptr, win_ptr, color);
        else
            ft_bresenham_hor(x2, y2, x1, y1, mlx_ptr, win_ptr, color);
    }
    else
    {
        if (y1 < y2)
            ft_bresenham_ver(x1, y1, x2, y2, mlx_ptr, win_ptr, color);
        else
            ft_bresenham_ver(x2, y2, x1, y1, mlx_ptr, win_ptr, color);
    }
}

void    ft_draw_lines(t_point **arr_lst, int len_x, int len_y, void *mlx_ptr, void *win_ptr)
{
    int     i;
    int     j;

    i = 0;
    while (i < len_y)
    {
        j = 0;
        while (j < len_x)
        {
            if (j + 1 < len_x)
                ft_bresenham(arr_lst[i][j].x + DW / 2, arr_lst[i][j].y + DH / 2, arr_lst[i][j + 1].x + DW / 2, arr_lst[i][j + 1].y + DH / 2, mlx_ptr, win_ptr, 0xFFFFFF);
            if (i + 1 < len_y)
                ft_bresenham(arr_lst[i][j].x + DW / 2, arr_lst[i][j].y + DH / 2, arr_lst[i + 1][j].x + DW / 2, arr_lst[i + 1][j].y + DH / 2, mlx_ptr, win_ptr, 0xFFFFFF);
            j++;
        }
        i++;
    }
}

void	ft_rotate(t_param* p)
{
    int     i;
    int     j;
//    int     k;
    float   x;
    float   y;
    float   z;

    i = 0;
    while (i < p->len_y) {
        j = 0;
        while (j < p->len_x) {
//            k = 0;
//            while (k < 3) {
                x = p->arr_lst[i][j].x;
                y = p->arr_lst[i][j].y;
                z = p->arr_lst[i][j].z;
                if (p->angle_x) {
                    p->arr_lst[i][j].y = y * COS(p->angle_x) - z * SIN(p->angle_x);
                    p->arr_lst[i][j].z = y * SIN(p->angle_x) + z * COS(p->angle_x);
                }
                if (p->angle_y) {
                    p->arr_lst[i][j].x = x * COS(p->angle_y) + z * SIN(p->angle_y);
                    p->arr_lst[i][j].z = z * COS(p->angle_y) - x * SIN(p->angle_y);
                }
                if (p->angle_z) {
                    p->arr_lst[i][j].x = x * COS(p->angle_z) - y * SIN(p->angle_z);
                    p->arr_lst[i][j].y = x * SIN(p->angle_z) + y * COS(p->angle_z);
                }
//                k++;
//            }
            j++;
        }
        i++;
    }

}

void ft_print(t_point **arr_lst, int len_x, int len_y)
{
    int     i;
    int     j;

    i = 0;
    while (i < len_y)
    {
        j = 0;
        while (j < len_x)
        {
            printf("(%i, %i, %i) ", (int)arr_lst[i][j].x, (int)arr_lst[i][j].y, (int)arr_lst[i][j].z);
            j++;
        }
        printf("\n");
        i++;
    }
    printf("\n- - - - - - - - - - - - - - - - - - - - - -\n");

}

void ft_add_coords(t_point **arr_lst, int len_x, int len_y)
{
    int     i;
    int     j;
    int     d;
    int     len;

    len = len_x * len_y;
    d = 500 / len_y;
    i = 0;
    while (i < len_y)
    {
        j = 0;
        while (j < len_x)
        {
            arr_lst[i][j].x = (j == 0) ? 0 - len_x * d / 2 : arr_lst[i][j - 1].x + d;
            arr_lst[i][j].y = (i == 0) ? 0 - len_y * d / 2: arr_lst[i - 1][j].y + d;
            arr_lst[i][j].z = arr_lst[i][j].z_init * d;
            arr_lst[i][j].x_p = 0;
            arr_lst[i][j].y_p = 0;
            arr_lst[i][j].z_p = 0;


//            arr_lst[i][j].dx = arr_lst[i][j].x + DW / 2;
//            arr_lst[i][j].dy = arr_lst[i][j].y + DH / 2;
//            arr_lst[i][j].dz = arr_lst[i][j].z;
//            arr_lst[i][j].ax = 0;
//            arr_lst[i][j].ay = 0;
//            arr_lst[i][j].az = 0;
            j++;
        }
        i++;
    }
}

int ft_close_window(void)
{
    exit(0);
}

void ft_add_angle(t_param *p, int x, int y, int z)
{
    p->angle_x += x;
    p->angle_y += y;
    p->angle_z += z;
}

void ft_equ_angle(t_param *p, int x, int y, int z)
{
    p->angle_x = x;
    p->angle_y = y;
    p->angle_z = z;
}


void ft_scale(t_param *p, float scale)
{
    int     i;
    int     j;
    float     x;
    float     y;
    float     z;

    i = 0;
    while (i < p->len_y)
    {
        j = 0;
        while (j < p->len_x)
        {
            x = p->arr_lst[i][j].x;
            y = p->arr_lst[i][j].y;
            z = p->arr_lst[i][j].z;
            p->arr_lst[i][j].x = x * scale;
            p->arr_lst[i][j].y = y * scale;
            p->arr_lst[i][j].z = z * scale;
            j++;
        }
        i++;
    }
}

void ft_move(t_param *p)
{
    int        i;
    int        j;
    float     x;
    float     y;
    float     z;

    i = 0;
    while (i < p->len_y)
    {
        j = 0;
        while (j < p->len_x)
        {
            x = p->arr_lst[i][j].x;
            y = p->arr_lst[i][j].y;
            z = p->arr_lst[i][j].z;
//            p->arr_lst[i][j].x = x + p->move_x;
//            p->arr_lst[i][j].y = y + p->move_y;
//            p->arr_lst[i][j].z = z + p->move_z;
            p->arr_lst[i][j].z = p->arr_lst[i][j].z_p;
            j++;
        }
        i++;
    }
}

void	ft_perspective(t_param *p, int near)
{
    int i;
    int j;
    int	x;
    int y;
    int z;

    i = 0;
    while (i < p->len_y)
    {
        j = 0;
        while (j < p->len_x)
        {
            x = p->arr_lst[i][j].x;
            y = p->arr_lst[i][j].y;
            z = p->arr_lst[i][j].z - 3000;
            p->arr_lst[i][j].x_p = p->arr_lst[i][j].x;
            p->arr_lst[i][j].y_p = p->arr_lst[i][j].y;
            p->arr_lst[i][j].z_p = p->arr_lst[i][j].z;
            if (z)
            {
                p->arr_lst[i][j].x = near * x / z;
                p->arr_lst[i][j].y = near * y / z;
                p->arr_lst[i][j].z = near;
            }

            j++;
        }
        i++;
    }
}

void	ft_non_perspective(t_param *p)
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

int ft_key_press(int keycode, void *param)
{
    t_param *p;

    p = (t_param*)param;


    if (keycode == 53)
        ft_close_window();

//    if (keycode == 12)
//        ft_draw_lines(p->arr_lst, p->len_x, p->len_y, p->mlx_ptr, p->win_ptr);

    /* A */
    if (keycode == 0)
    {
        mlx_clear_window(p->mlx_ptr, p->win_ptr);
        ft_add_angle(p, 0, 0, -1);
        ft_rotate(p);
        ft_draw_lines(p->arr_lst, p->len_x, p->len_y, p->mlx_ptr, p->win_ptr);
       // ft_print(p->arr_lst, p->len_x, p->len_y);
    }
    /* D */
    if (keycode == 2)
    {
        mlx_clear_window(p->mlx_ptr, p->win_ptr);
        ft_add_angle(p, 0, 0, 1);
        ft_rotate(p);
        ft_draw_lines(p->arr_lst, p->len_x, p->len_y, p->mlx_ptr, p->win_ptr);
//        ft_print(p->arr_lst, p->len_x, p->len_y);
    }
    /* W */
    if (keycode == 13)
    {
        mlx_clear_window(p->mlx_ptr, p->win_ptr);
        ft_add_angle(p, 1, 0, 0);
        ft_rotate(p);
        ft_draw_lines(p->arr_lst, p->len_x, p->len_y, p->mlx_ptr, p->win_ptr);
    }
    /* S */
    if (keycode == 1)
    {
        mlx_clear_window(p->mlx_ptr, p->win_ptr);
        ft_add_angle(p, -1, 0, 0);
        ft_rotate(p);
//        ft_print(p->arr_lst, p->len_x, p->len_y);
        ft_draw_lines(p->arr_lst, p->len_x, p->len_y, p->mlx_ptr, p->win_ptr);
    }

    /* Q */
    if (keycode == 12)
    {
        mlx_clear_window(p->mlx_ptr, p->win_ptr);
        ft_add_coords(p->arr_lst, p->len_x, p->len_y);
        ft_draw_lines(p->arr_lst, p->len_x, p->len_y, p->mlx_ptr, p->win_ptr);
//        ft_print(p->arr_lst, p->len_x, p->len_y);
    }

    if (keycode == 18)
    {
        mlx_clear_window(p->mlx_ptr, p->win_ptr);
        ft_add_coords(p->arr_lst, p->len_x, p->len_y);
        ft_add_angle(p, 0, 0, -45);
        ft_rotate(p);
        ft_equ_angle(p, 60, 0, 0);
        ft_rotate(p);
        ft_draw_lines(p->arr_lst, p->len_x, p->len_y, p->mlx_ptr, p->win_ptr);
    }

    if (keycode == 19)
    {
        mlx_clear_window(p->mlx_ptr, p->win_ptr);
//        ft_add_coords(p->arr_lst, p->len_x, p->len_y);
        //    ft_print(p->arr_lst, p->len_x, p->len_y);
//        ft_add_angle(p, 0, 0, -45);
//        ft_add_angle(p, 0, 0, -45);
//        ft_rotate(p, 3);
//        ft_add_angle(p, 0, 0, 45);
//        ft_rotate(p, 3);
//        ft_equ_angle(p, 60, 0, -45);
//        ft_rotate(p);
//        ft_moving(p->arr_lst, p->len_x, p->len_y, 500);
//        ft_equ_angle(p, 0, 0, 55);
//        ft_equ_angle(p, 60, 0, 0);
//        ft_rotate(p);
//        ft_add_coords(p->arr_lst, p->len_x, p->len_y);

        p->is_perspective = 1;
        ft_perspective(p, -2000);
        ft_move(p);
        ft_draw_lines(p->arr_lst, p->len_x, p->len_y, p->mlx_ptr, p->win_ptr);
    }
    return (0);
}

int mouse_press(int button, int x, int y, void *param)
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
    ft_draw_lines(p->arr_lst, p->len_x, p->len_y, p->mlx_ptr, p->win_ptr);
    return (0);
}

//int mouse_scroll(int button, int x, int y, void *param)
//{
//    t_param *p;
//    float q;
//    float w;
//
//    p = (t_param*)param;
//    if (button == 4)
//    {
//        q = (float)x;
//        w = (float)y;
//        p->scale += 1;
//    }
//    return (0);
//}

int mouse_release(int button, int x, int y, void *param)
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

int mouse_move(int x, int y, void *param)
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
        if (p->is_perspective == 1)
            ft_perspective(p, -2000);
        mlx_clear_window(p->mlx_ptr, p->win_ptr);
        ft_draw_lines(p->arr_lst, p->len_x, p->len_y, p->mlx_ptr, p->win_ptr);
    }
    if (p->press_mouse_r == 1)
    {
        if (p->move_x == 0)
        {
            p->move_x = x;
            return (0);
        }
        else
            p->move_x = x - p->move_x;
        if (p->move_y == 0)
        {
            p->move_y = y;
            return (0);
        }
        else
            p->move_y = y - p->move_y;
       // printf("init_x = %f, init_y = %f, x = %i, y = %i\n", p->move_x, p->move_y, x, y);
        p->move_x = x - p->move_x;
        p->move_y = y - p->move_y;
        printf("move_x = %f, move_y = %f, x = %i, y = %i\n", p->move_x, p->move_y, x, y);
        ft_move(p);
        mlx_clear_window(p->mlx_ptr, p->win_ptr);
        ft_draw_lines(p->arr_lst, p->len_x, p->len_y, p->mlx_ptr, p->win_ptr);
    }
    return (0);
}




void    ft_open_window(t_point **arr_lst, int len_x, int len_y)
{
    void	*mlx_ptr;
    void	*win_ptr;
    t_param p;
//    int d;

//    d = 500 / len_y;
    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, 1600, 900, "80s_team");
//    len_x = 1;
//    len_y = 1;
//    arr_lst[0][0].x = 11;

    p.arr_lst = arr_lst;
    p.len_x = len_x;
    p.len_y = len_y;
    p.mlx_ptr = mlx_ptr;
    p.win_ptr = win_ptr;
    p.press_mouse_l = 0;
    p.press_mouse_r = 0;
    p.init_x = 0;
    p.init_y = 0;
    p.init_z = 0;
    p.angle_x = 0;
    p.angle_y = 0;
    p.angle_z = 0;
    p.move_x = 0;
    p.move_y = 0;
    p.move_z = 0;
    p.is_perspective = 0;
    ft_add_coords(arr_lst, len_x, len_y);
    ft_draw_lines(arr_lst, len_x, len_y, mlx_ptr, win_ptr);
//    printf("d = %i\n", d);
//    printf("cx = %i, cy = %i\n", len_x * d / 2, len_y * d / 2);
  //  printf("DW / 2 = %i, DH / 2 = %i\n", DW / 2, DH / 2);
   // printf("x = %i, y = %i\n", len_x * d / 2 - arr_lst[0][0].x + len_x * d / 2, len_y * d / 2 - arr_lst[0][0].y + len_y * d / 2);
 //   ft_rotate(arr_lst, ft_degree_to_rad(0, 0, -45), len_x, len_y);
  //  ft_rotate(arr_lst, ft_degree_to_rad(60, 0, 0), len_x, len_y);
  //  ft_moving(arr_lst, len_x, len_y, 500);

    mlx_hook(win_ptr, 17, 0, ft_close_window, 0);
    mlx_hook(win_ptr, 2, 0, ft_key_press, &p);
    mlx_hook(win_ptr, 4, 0, mouse_press, &p);
    mlx_hook(win_ptr, 5, 0, mouse_release, &p);
    mlx_hook(win_ptr, 6, 0, mouse_move, &p);
//    mlx_mouse_hook(win_ptr, mouse_press, &p);
//    mlx_mouse_hook(win_ptr, mouse_move, &p);
//    ft_bresenham(100, 100, 300, 300, mlx_ptr, win_ptr, 0xFFFFFF);
//    ft_iso_modifier(mlx_ptr, win_ptr, arr_lst, len_x, len_y);
    mlx_loop(mlx_ptr);
}

