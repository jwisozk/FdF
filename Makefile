# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: twill <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/06 20:19:57 by twill             #+#    #+#              #
#    Updated: 2019/05/29 22:59:16 by twill            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = clang
CFLAGS = -Wall -Wextra -Werror
HEADERS = fdf.h
# LIBMLX = -L minilibx_macos/ -lmlx -framework OpenGL -framework AppKit
LIBMLX = -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit
LIBFT = libft/libft.a
MAKE_LIBFT = make -C libft
SOURCE = main.c \
		 algo.c \
		 bresenham.c \
		 fill.c \
		 extra.c \
		 input1.c \
		 input2.c \
		 input3.c \
		 projection.c \
		 rotate.c
OBJ = $(SOURCE:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE_LIBFT)
	$(CC) $(CFLAGS) $^ $(LIBFT) $(LIBMLX) -o $(NAME)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ)
	$(MAKE_LIBFT) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)

re: fclean all

.PHONY: all fclean re clean