/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twill <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 20:38:16 by twill             #+#    #+#             */
/*   Updated: 2019/06/30 20:38:17 by twill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "/usr/local/include/mlx.h"
# define H_DIST_BTWN_TWO_POINT 20
# define V_DIST_BTWN_TWO_POINT 20
# define DW 1600
# define DH 900
# define LIMIT_SCALE_UP 3000
# define LIMIT_SCALE_DOWN 30
# define COS(x) cos(x * M_PI / 180)
# define SIN(x) sin(x * M_PI / 180)
# define DEFAULT_COLOR 16777215
# define DIST 500

typedef struct		s_angle
{
	int				x;
	int				y;
	int				z;
}					t_angle;

typedef struct		s_point
{
	float			x;
	float			y;
	float			z;
	float			z_init;
	float			x_p;
	float			y_p;
	float			z_p;
	float			x_move;
	float			y_move;
	float			z_move;
	int				color;
}					t_point;

typedef struct		s_param
{
	int				fd;
	t_point			**arr_lst;
	int				max_z;
	int				len_x;
	int				len_y;
	int				init_x;
	int				init_y;
	int				init_z;
	int				angle_x;
	int				angle_y;
	int				angle_z;
	float			move_x;
	float			move_y;
	float			move_z;
	int				press_mouse_l;
	void			*mlx_ptr;
	void			*win_ptr;
	int				is_perspective;
	int				is_fillcolor;
	int				fillcolor;
	int				var1;
	int				var2;
	int				var3;
	int				var4;
	int				var5;
	unsigned int	var6;
	unsigned int	var7;
	int				var8;
	int				var9;
	int				var10;
	int				var11;
	int				var12;
	t_point			*pnt;
}					t_param;

typedef struct		s_color_params
{
	unsigned char	a1;
	unsigned char	r1;
	unsigned char	g1;
	unsigned char	b1;
	unsigned char	a2;
	unsigned char	r2;
	unsigned char	g2;
	unsigned char	b2;
	int				delta_a;
	int				delta_r;
	int				delta_g;
	int				delta_b;
	int				m_delta;
	int				step;
}					t_color_params;

void				draw_line(void *mlx_ptr, void *win_ptr, float x1, float y1,
					float x2, float y2, int color);
void				ft_wire_designer(void *mlx_ptr, void *win_ptr,
					t_point **arr_lst, int len_x, int len_y);
void				ft_open_window(t_param *p);
void				ft_bresenham(t_param *p, int i, int j, int v);
void				ft_fill_quadrilateral(t_param *p, int i, int j);
void				ft_set_var_to_zero(t_param *p);
int					ft_is_same_sign(float first, float second, float third);
void				ft_set_var_to_zero(t_param *p);
int					ft_close_window(void *param);
void				ft_rotate(t_param *p);
void				ft_equ_angle(t_param *p, int x, int y, int z);
void				ft_return_position(t_param *p);
int					ft_key_press(int keycode, void *param);
int					ft_mouse_press(int button, int x, int y, void *param);
int					ft_mouse_release(int button, int x, int y, void *param);
int					ft_mouse_move(int x, int y, void *param);
void				ft_add_coords(t_param *p);
void				ft_perspective(t_param *p, int near);
void				ft_non_perspective(t_param *p);
void				ft_standart_key(t_param *p);
void				ft_iso_key(t_param *p);
void				ft_persp_key(t_param *p);
void				ft_switch_color(t_param *p);
void				ft_one_key(t_param *p, int x, int y, int z);
void				ft_scale(t_param *p, float scale);
void				ft_draw_lines(t_param *p);
int					ft_getlen_x(char **arr);
int					ft_print_error(char *str);
void				ft_init_param(t_param *p);

#endif
