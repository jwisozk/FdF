/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 20:08:42 by jwisozk           #+#    #+#             */
/*   Updated: 2019/05/28 22:58:36 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft/libft.h"
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <stdio.h>
# define BUFF_SIZE 256
int	ft_getlen_x(char **arr)
{
    int len;

    len = 0;
    while (arr[len] != NULL)
        len++;
    return (len);
}

t_list *ft_get_lst_with_len_y(int fd)
{
    int     len;
    char 	*line;
    t_list  *lst;
    t_list  *tmp;

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

static int		ft_print_error(char *str)
{
    ft_putstr(str);
    ft_putchar('\n');
    return (0);
}

void ft_fill_lst(t_point **arr_lst, int j, int i, char **arr_str)
{
    char	*color_str;
    arr_lst[i][j].x = j;
    arr_lst[i][j].y = i;
    arr_lst[i][j].z = ft_atoi(arr_str[j]);
    if (!(color_str = ft_strchr(arr_str[j], ',')))
        arr_lst[i][j].color = 0;
    else
        arr_lst[i][j].color = ft_atoi(color_str + 1);
}

t_point **ft_fill_arr_lst(t_point **arr_lst, t_list *lst, int *len_x)
{
    int     tmp;
    char    **arr_str;
    int     i;
    int     j;

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

t_point	**ft_create_arr_lst(t_list *lst, int *len_x)
{
    t_point	**arr_lst;

    if (!(arr_lst = (t_point**)malloc(sizeof(t_point*) * ((int)lst->content_size + 1))))
        return (NULL);
    arr_lst[lst->content_size] = NULL;
    arr_lst = ft_fill_arr_lst(arr_lst, lst, len_x);
    return (arr_lst);
}

void ft_add_coords(t_point **arr_lst, int len_x, int len_y)
{
    int     i;
    int     j;
    int     d;

    d = (len_x > len_y) ? DH / len_x : DH / len_y;
//    printf("dx : %f, dy : %f\n", dx , dy);
    i = 0;
    while (i < len_y)
    {
        j = 0;
        while (j < len_x)
        {
            arr_lst[i][j].x = (j == 0) ? 100 + (DW - d * len_x) / 2 : arr_lst[i][j - 1].x + d;
            arr_lst[i][j].y = (i == 0) ? 100 + (DH - d * len_y) / 2 : arr_lst[i - 1][j].y + d;
          printf("(%i, %i) ", arr_lst[i][j].x, arr_lst[i][j].y);
          j++;
        }
        printf("\n");
        i++;
    }
}

int	main(int argc, char **argv)
{
    int		fd;
    int     len_x;
    int     len_y;
    t_list	*lst;
    t_point	**arr_lst;

    if (argc == 2)
    {
        if ((fd = open(argv[1], O_RDONLY)) == -1)
            return (ft_print_error("error"));

        lst = ft_get_lst_with_len_y(fd);
        if (!(arr_lst = ft_create_arr_lst(lst, &len_x)))
        {
            ft_lstdel(&lst, ft_del);
            return (ft_print_error("error"));
        }
        len_y = (int)lst->content_size;
        ft_add_coords(arr_lst, len_x, len_y);
        ft_open_window(arr_lst, len_x, len_y);
//        printf("len_x = %i, len_y = %i\n", len_x, len_y);
        ///
//        int j;
//        int i = 0;
//        printf("len_y = %i\n", len_y);
//        while (i < len_y)
//        {
//            j = 0;
//            while (j < len_x)
//            {
//                printf("%d ", (int)arr_lst[i][j].z);
////                printf("x : %d, y : %d\n", (int)arr_lst[i][j].x, (int)arr_lst[i][j].y);
//                j++;
//            }
//            printf("\n");
//            i++;
//        }

        ///



    }

        return (0);
}
