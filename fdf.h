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
#include "libft/libft.h"
#include "mlx.h"
#define DW 1600
#define DH 900
//#define ONE_DEGREE M_PI / 180
#define COS(x) cos(x * M_PI / 180)
#define SIN(x) sin(x * M_PI / 180)

typedef  struct     s_angle
{
    int             x;
    int             y;
    int             z;
}                   t_angle;
typedef struct 		s_point
{
    int             ax;
    int             ay;
    int             az;
    int             dx;
    int             dy;
    int             dz;
    int             x;
    int 	        y;
    int	            z;
	int				color;
}					t_point;

typedef  struct     s_param
{
    t_point         **arr_lst;
    int             len_x;
    int             len_y;
    void	        *mlx_ptr;
    void	        *win_ptr;
}                   t_param;

void	draw_line(void *mlx_ptr, void *win_ptr, float x1, float y1,
		float x2, float y2,	int color);
void    ft_wire_designer(void *mlx_ptr, void *win_ptr,
        t_point **arr_lst, int len_x, int len_y);
//void    ft_open_new_window(t_point **arr_lst, int len_x, int len_y);
void    ft_open_window(t_point **arr_lst, int len_x, int len_y);

#endif
