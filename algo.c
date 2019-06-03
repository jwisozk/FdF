#include "mlx.h"
#include "fdf.h"

void ft_bresenham_hor(int x1, int y1, int x2, int y2, void *mlx_ptr, void *win_ptr, int color)
{
    int dx;
    int dy;
    int x;
    int y;
    int slope;

    dx = x2 - x1;
    dy = y2 - y1;
    slope = 2 * dy - dx;
    x = x1;
    y = y1;
    while (x <= x2)
    {
        mlx_pixel_put(mlx_ptr, win_ptr, x, y, color);
        if (slope >= 0)
        {
            y++;
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
    
    dx = x2 - x1;
    dy = y2 - y1;
    slope = 2 * dx - dy;
    x = x1;
    y = y1;
    while (y <= y2)
    {
        mlx_pixel_put(mlx_ptr, win_ptr, x, y, color);
        if (slope >= 0)
        {
            x++;
            slope -= 2 * dy;
        }
        slope += 2 * dx;
        y++;
    }
}

void    ft_draw_lines(t_point **arr_lst, int len_x, int len_y, void *mlx_ptr, void *win_ptr)
{
    int     i;
    int     j;
//    printf("dx : %f, dy : %f\n", dx , dy);
    i = 0;
    while (i < len_y)
    {
        j = 0;
        while (j < len_x)
        {
            if (j + 1 < len_x)
                ft_bresenham_hor(arr_lst[i][j].x, arr_lst[i][j].y, arr_lst[i][j + 1].x, arr_lst[i][j + 1].y, mlx_ptr, win_ptr, 0xFFFFFF);
            if (i + 1 < len_y)
                ft_bresenham_ver(arr_lst[i][j].x, arr_lst[i][j].y, arr_lst[i + 1][j].x, arr_lst[i + 1][j].y, mlx_ptr, win_ptr, 0xFFFFFF);
//          printf("(%i, %i) ", (int)arr_lst[i][j].x, (int)arr_lst[i][j].y);
            j++;
        }
//        printf("\n");
        i++;
    }
}

void    ft_open_window(t_point **arr_lst, int len_x, int len_y)
{
    void	*mlx_ptr;
    void	*win_ptr;

    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, 1600, 900, "80s_team");
//    len_x = 1;
//    len_y = 1;
//    arr_lst[0][0].x = 11;
    ft_draw_lines(arr_lst, len_x, len_y, mlx_ptr, win_ptr);
//    ft_bresenham(100, 100, 100, 136, mlx_ptr, win_ptr, 0xFFFFFF);
//    ft_iso_modifier(mlx_ptr, win_ptr, arr_lst, len_x, len_y);

    mlx_loop(mlx_ptr);
}

