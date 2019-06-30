/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 18:39:19 by jwisozk           #+#    #+#             */
/*   Updated: 2019/06/21 14:01:44 by twill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define H_DIST_BTWN_TWO_POINT 20
# define V_DIST_BTWN_TWO_POINT 20

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <fcntl.h>
#include "libft/libft.h"
#include "mlx.h"
#define DW 1600
#define DH 900
#define LIMIT_SCALE_UP 3000
#define LIMIT_SCALE_DOWN 100
//#define ONE_DEGREE M_PI / 180
#define COS(x) cos(x * M_PI / 180)
#define SIN(x) sin(x * M_PI / 180)
#define DEFAULT_COLOR 16777215
#define DIST 400

typedef  struct     s_angle
{
    int             x;
    int             y;
    int             z;
}                   t_angle;
typedef struct 		s_point
{
    float           x;
    float 	        y;
    float	        z;
    float           z_init;
    float           x_p;
    float           y_p;
    float           z_p;
    float           x_move;
    float           y_move;
    float           z_move;
	int				color;
}					t_point;

typedef  struct     s_param
{
    t_point         **arr_lst;
    int             len_x;
    int             len_y;
    int             init_x;
    int             init_y;
    int             init_z;
    int             angle_x;
    int             angle_y;
    int             angle_z;
    float           move_x;
    float           move_y;
    float           move_z;
    int             press_mouse_l;
    int             press_mouse_r;
    void	        *mlx_ptr;
    void	        *win_ptr;
    int             is_perspective;
    int             is_fillcolor;
    int 			fillcolor;
    int 			var1;
    int 			var2;
    int 			var3;
    int 			var4;
    int 			var5;
    unsigned int 	var6;
    unsigned int 	var7;
	int 			var8;
	int 			var9;
	int 			var10;
	int 			var11;
	int 			var12;
	t_point			*point;
//    int             is_isometric;
}                   t_param;
typedef struct 		s_color_params
{
	unsigned char	a1;
	unsigned char	r1;
	unsigned char	g1;
	unsigned char	b1;
	unsigned char	a2;
	unsigned char	r2;
	unsigned char	g2;
	unsigned char	b2;
	int 			delta_a;
	int 			delta_r;
	int 			delta_g;
	int 			delta_b;
	int 			m_delta;
	int 			step;
}					t_color_params;
void	draw_line(void *mlx_ptr, void *win_ptr, float x1, float y1,
		float x2, float y2,	int color);
void    ft_wire_designer(void *mlx_ptr, void *win_ptr,
        t_point **arr_lst, int len_x, int len_y);
//void    ft_open_new_window(t_point **arr_lst, int len_x, int len_y);
void    ft_open_window(t_param *p);
void    ft_bresenham(t_param *p, int i, int j, int v);
//void    ft_bresenham(int x1, int y1, int x2, int y2, void *mlx_ptr, void *win_ptr, int color);
void	ft_fill_quadrilateral(t_param *p, int i, int j);
void	ft_set_var_to_zero(t_param *p);

#endif
