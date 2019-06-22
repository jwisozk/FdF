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
                ft_bresenham(arr_lst[i][j].dx, arr_lst[i][j].dy, arr_lst[i][j + 1].dx, arr_lst[i][j + 1].dy, mlx_ptr, win_ptr, 0xFFFFFF);
            if (i + 1 < len_y)
                ft_bresenham(arr_lst[i][j].dx, arr_lst[i][j].dy, arr_lst[i + 1][j].dx, arr_lst[i + 1][j].dy, mlx_ptr, win_ptr, 0xFFFFFF);
            j++;
        }
        i++;
    }
}

void	ft_rotate(t_point** arr_lst, t_angle *rad, int len_x, int len_y)
{
    int     i;
    int     j;
    int     x;
    int     y;
    int     z;
    int     dx;
    int     dy;
    int     dz;

    i = 0;
    while (i < len_y)
    {
        j = 0;
        while (j < len_x)
        {
            dx = arr_lst[i][j].dx;
            dy = arr_lst[i][j].dy;
            dz = arr_lst[i][j].dz;
            x = arr_lst[i][j].x;
            y = arr_lst[i][j].y;
            z = arr_lst[i][j].z;
            if (rad->x)
            {
                if (dx && dy)
                {
                    arr_lst[i][j].dx = dx * COS(1 * (arr_lst[i][j].az + rad->z)) - dy * SIN(1 * (arr_lst[i][j].az + rad->z));
                    arr_lst[i][j].dy = dx * SIN(1 * (arr_lst[i][j].az + rad->z)) + dy * COS(1 * (arr_lst[i][j].az + rad->z));
                    arr_lst[i][j].dy = dy * COS(1 * (arr_lst[i][j].ax + rad->x)) - dz * SIN(1 * (arr_lst[i][j].ax + rad->x));
                    arr_lst[i][j].dz = dy * SIN(1 * (arr_lst[i][j].ax + rad->x)) + dz * COS(1 * (arr_lst[i][j].ax + rad->x));
                }
                else
                {
                    //                arr_lst[i][j].dy = y * COS(1 * (arr_lst[i][j].ax + rad->x)) - z * SIN(1 * (arr_lst[i][j].ax + rad->x)) + DH / 2;
//                arr_lst[i][j].dz = y * SIN(1 * (arr_lst[i][j].ax + rad->x)) + z * COS(1 * (arr_lst[i][j].ax + rad->x)) + DH / 2;
                    arr_lst[i][j].dy = y * COS(1 * (arr_lst[i][j].ax + rad->x)) - z * SIN(1 * (arr_lst[i][j].ax + rad->x));
                    arr_lst[i][j].dz = y * SIN(1 * (arr_lst[i][j].ax + rad->x)) + z * COS(1 * (arr_lst[i][j].ax + rad->x));
                }



//
//                arr_lst[i][j].dx = arr_lst[i][j].dx * COS(1 * (arr_lst[i][j].az + rad->z)) - arr_lst[i][j].dy * SIN(1 * (arr_lst[i][j].az + rad->z));
//                arr_lst[i][j].dy = y * COS(1 * (arr_lst[i][j].ax + rad->x)) - z * SIN(1 * (arr_lst[i][j].ax + rad->x));
//                arr_lst[i][j].dz = y * SIN(1 * (arr_lst[i][j].ax + rad->x)) + z * COS(1 * (arr_lst[i][j].ax + rad->x));
                arr_lst[i][j].ax = (rad->x > 0) ?  arr_lst[i][j].ax + 1 :  arr_lst[i][j].ax - 1;
            }
            if (rad->y)
            {
                arr_lst[i][j].dx = x * COS(rad->y) + z * SIN(rad->y);
                arr_lst[i][j].dz = z * COS(rad->y) - x * SIN(rad->y);
            }
            if (rad->z)
            {
                if (dy && dz)
                {
                    arr_lst[i][j].dy = dy * COS(1 * (arr_lst[i][j].ax + rad->x)) - dz * SIN(1 * (arr_lst[i][j].ax + rad->x));
                    arr_lst[i][j].dz = dy * SIN(1 * (arr_lst[i][j].ax + rad->x)) + dz * COS(1 * (arr_lst[i][j].ax + rad->x));
                }
//                arr_lst[i][j].dx = x * COS(1 * (arr_lst[i][j].az + rad->z)) - y * SIN(1 * (arr_lst[i][j].az + rad->z)) + DW / 2;
//                arr_lst[i][j].dy = x * SIN(1 * (arr_lst[i][j].az + rad->z)) + y * COS(1 * (arr_lst[i][j].az + rad->z)) + DH / 2;
                arr_lst[i][j].dx = x * COS(1 * (arr_lst[i][j].az + rad->z)) - y * SIN(1 * (arr_lst[i][j].az + rad->z));
                arr_lst[i][j].dy = x * SIN(1 * (arr_lst[i][j].az + rad->z)) + y * COS(1 * (arr_lst[i][j].az + rad->z));


//                arr_lst[i][j].dy = y * COS(1 * (arr_lst[i][j].ax + rad->x)) - z * SIN(1 * (arr_lst[i][j].ax + rad->x)) + DH / 2;
//                arr_lst[i][j].dz = arr_lst[i][j].dy * SIN(1 * (arr_lst[i][j].ax + rad->x)) + arr_lst[i][j].dz * COS(1 * (arr_lst[i][j].ax + rad->x));
//                arr_lst[i][j].dx = x * COS(1 * (arr_lst[i][j].az + rad->z)) - y * SIN(1 * (arr_lst[i][j].az + rad->z));
//                arr_lst[i][j].dy = x * SIN(1 * (arr_lst[i][j].az + rad->z)) + y * COS(1 * (arr_lst[i][j].az + rad->z));
                arr_lst[i][j].az = (rad->z > 0) ?  arr_lst[i][j].az + 1 :  arr_lst[i][j].az - 1;
            }
            j++;
        }
        i++;
    }
}

t_angle    *ft_degree_to_rad(int x, int y, int z)
{
    t_angle *rad;

    rad = (t_angle*)malloc(sizeof(t_angle));
    rad->x = x;
    rad->y = y;
    rad->z = z;
    return (rad);
}

void ft_moving(t_point **arr_lst, int len_x, int len_y, int offset)
{
    int     i;
    int     j;

    i = 0;
    while (i < len_y)
    {
        j = 0;
        while (j < len_x)
        {
            arr_lst[i][j].x += offset;
            arr_lst[i][j].y += offset;
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
            printf("(%i, %i) ", arr_lst[i][j].dx, arr_lst[i][j].dy);
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
            arr_lst[i][j].z *= d;
            arr_lst[i][j].dx = arr_lst[i][j].x + DW / 2;
            arr_lst[i][j].dy = arr_lst[i][j].y + DH / 2;
            arr_lst[i][j].dz = arr_lst[i][j].z;
            arr_lst[i][j].ax = 0;
            arr_lst[i][j].ay = 0;
            arr_lst[i][j].az = 0;
            j++;
        }
        i++;
    }
}

int ft_close_window(void)
{
    exit(0);
}

int key_press(int keycode, void *param)
{
    t_param *p;

    p = (t_param*)param;

    mlx_clear_window(p->mlx_ptr, p->win_ptr);
    if (keycode == 53)
        ft_close_window();

//    if (keycode == 12)
//        ft_draw_lines(p->arr_lst, p->len_x, p->len_y, p->mlx_ptr, p->win_ptr);

    /* A */
    if (keycode == 0)
    {
        ft_rotate(p->arr_lst, ft_degree_to_rad(0, 0, -1), p->len_x, p->len_y);
        ft_draw_lines(p->arr_lst, p->len_x, p->len_y, p->mlx_ptr, p->win_ptr);
        ft_print(p->arr_lst, p->len_x, p->len_y);
    }
    /* D */
    if (keycode == 2)
    {
        ft_rotate(p->arr_lst, ft_degree_to_rad(0, 0, 1), p->len_x, p->len_y);
        ft_draw_lines(p->arr_lst, p->len_x, p->len_y, p->mlx_ptr, p->win_ptr);
//        ft_print(p->arr_lst, p->len_x, p->len_y);
    }
    /* W */
    if (keycode == 13)
    {
        ft_rotate(p->arr_lst, ft_degree_to_rad(1, 0, 0), p->len_x, p->len_y);
        ft_draw_lines(p->arr_lst, p->len_x, p->len_y, p->mlx_ptr, p->win_ptr);
    }
    /* S */
    if (keycode == 1)
    {
        ft_rotate(p->arr_lst, ft_degree_to_rad(-1, 0, 0), p->len_x, p->len_y);
//        ft_print(p->arr_lst, p->len_x, p->len_y);
        ft_draw_lines(p->arr_lst, p->len_x, p->len_y, p->mlx_ptr, p->win_ptr);
    }

    /* Q */
    if (keycode == 12)
    {
        ft_add_coords(p->arr_lst, p->len_x, p->len_y);
        ft_draw_lines(p->arr_lst, p->len_x, p->len_y, p->mlx_ptr, p->win_ptr);
//        ft_print(p->arr_lst, p->len_x, p->len_y);
    }

    if (keycode == 18)
    {
        ft_rotate(p->arr_lst, ft_degree_to_rad(0, 0, -45), p->len_x, p->len_y);
//        ft_rotate(p->arr_lst, ft_degree_to_rad(60, 0, 0), p->len_x, p->len_y);
//        ft_moving(p->arr_lst, p->len_x, p->len_y, 500);
        ft_draw_lines(p->arr_lst, p->len_x, p->len_y, p->mlx_ptr, p->win_ptr);
    }
    return (0);
}

void    ft_open_window(t_point **arr_lst, int len_x, int len_y)
{
    void	*mlx_ptr;
    void	*win_ptr;
    t_param p;
    int d;

    d = 500 / len_y;
    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, 1600, 900, "80s_team");
//    len_x = 1;
//    len_y = 1;
//    arr_lst[0][0].x = 11;
    ft_add_coords(arr_lst, len_x, len_y);
    ft_draw_lines(arr_lst, len_x, len_y, mlx_ptr, win_ptr);
    p.arr_lst = arr_lst;
    p.len_x = len_x;
    p.len_y = len_y;
    p.mlx_ptr = mlx_ptr;
    p.win_ptr = win_ptr;
    printf("d = %i\n", d);
//    printf("cx = %i, cy = %i\n", len_x * d / 2, len_y * d / 2);
  //  printf("DW / 2 = %i, DH / 2 = %i\n", DW / 2, DH / 2);
   // printf("x = %i, y = %i\n", len_x * d / 2 - arr_lst[0][0].x + len_x * d / 2, len_y * d / 2 - arr_lst[0][0].y + len_y * d / 2);
 //   ft_rotate(arr_lst, ft_degree_to_rad(0, 0, -45), len_x, len_y);
  //  ft_rotate(arr_lst, ft_degree_to_rad(60, 0, 0), len_x, len_y);
  //  ft_moving(arr_lst, len_x, len_y, 500);

    mlx_hook(win_ptr, 17, 0, ft_close_window, 0);
    mlx_hook(win_ptr, 2, 0, key_press, &p);
//    ft_bresenham(100, 100, 300, 300, mlx_ptr, win_ptr, 0xFFFFFF);
//    ft_iso_modifier(mlx_ptr, win_ptr, arr_lst, len_x, len_y);
    mlx_loop(mlx_ptr);
}

