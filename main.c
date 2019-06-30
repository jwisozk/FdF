/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twill <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 22:01:20 by twill             #+#    #+#             */
/*   Updated: 2019/06/30 22:01:22 by twill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_list	*ft_get_lst_with_len_y(int fd)
{
	int		len;
	char	*line;
	t_list	*lst;
	t_list	*tmp;

	len = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (len == 0)
		{
			if (!(lst = ft_lstnew(line, ft_strlen(line) + 1)))
				return (NULL);
		}
		else
		{
			if (!(tmp = ft_lstnew(line, ft_strlen(line) + 1)))
			{
				ft_lstdel(&lst, ft_del);
				return (NULL);
			}
			ft_lstadd_back(&lst, tmp);
		}
		lst->content_size = ++len;
	}
	return (lst);
}

static void		ft_fill_lst(t_point **arr_lst, int j, int i, char **arr_str)
{
	char	*color_str;
	char	*next_char_ptr;

	arr_lst[i][j].z_init = ft_atoi(arr_str[j]);
	if (!(color_str = ft_strchr(arr_str[j], ',')) || *(color_str + 1) == '\0')
		arr_lst[i][j].color = DEFAULT_COLOR;
	else
	{
		next_char_ptr = color_str + 1;
		arr_lst[i][j].color = ft_atoi_base(&next_char_ptr);
	}
}

static t_point	**ft_fill_arr_lst(t_point **arr_lst, t_list *lst, int *len_x)
{
	int		tmp;
	char	**arr_str;
	int		i;
	int		j;

	i = 0;
	while (lst != NULL)
	{
		arr_str = ft_strsplit(lst->content, ' ');
		*len_x = ft_getlen_x(arr_str);
		if ((i > 0 && *len_x != tmp) ||
			!(arr_lst[i] = (t_point*)malloc(sizeof(t_point) * *len_x)))
			return ((t_point**)ft_free_all((void**)arr_lst, i));
		j = 0;
		while (j < *len_x)
		{
			ft_fill_lst(arr_lst, j, i, arr_str);
			j++;
		}
		tmp = *len_x;
		i++;
		lst = lst->next;
	}
	return (arr_lst);
}

static t_point	**ft_create_arr_lst(t_list *lst, t_param *p)
{
	t_point	**arr_lst;

	if (!(arr_lst = (t_point**)malloc(sizeof(t_point*) * (p->len_y + 1))))
		return (NULL);
	arr_lst[p->len_y] = NULL;
	arr_lst = ft_fill_arr_lst(arr_lst, lst, &(p->len_x));
	return (arr_lst);
}

int				main(int argc, char **argv)
{
	int		fd;
	t_param	p;
	t_list	*lst;

	if (argc == 2)
	{
		if ((fd = open(argv[1], O_RDONLY)) == -1)
			return (ft_print_error("Error: file not found"));
		if ((lst = ft_get_lst_with_len_y(fd)) == NULL)
			ft_print_error("Error: file was not read");
		ft_init_param(&p, (int)lst->content_size);
		if (!(p.arr_lst = ft_create_arr_lst(lst, &p)))
		{
			ft_lstdel(&lst, ft_del);
			return (ft_print_error("Error: found wrong line length"));
		}
		ft_open_window(&p);
	}
	else
		ft_print_error("Usage: ./fdf <filename>");
	return (0);
}
