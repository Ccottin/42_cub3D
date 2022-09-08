# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccottin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/02 17:05:58 by ccottin           #+#    #+#              #
#    Updated: 2022/09/08 16:26:51 by ybendavi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D

SRCS	= srcs/init_map.c srcs/utils.c srcs/init.c srcs/ft_return.c srcs/main.c\
	srcs/set_info.c srcs/get_info_wall.c srcs/utils1.c srcs/set_info_map.c\
	srcs/raycaster.c srcs/events_handler.c srcs/key_handler.c\
	srcs/key_handler_p2.c srcs/init_player.c srcs/initcaster.c srcs/texture.c\
	srcs/init_map_utils.c srcs/ft_cub3d.c srcs/map_closed.c

SRCSDIR	= srcs

OBJS	= $(SRCS:%.c=%.o)

OBJSDIR	= objs

CC	= gcc

CFLAGS	= -Wall -Wextra -Werror -g3 

all	:	$(NAME)

%.o	:	%.c
		$(CC) $(CFLAGS) -I/usr/include -Imlx_Linux -I./includes -c $< -o $@

$(NAME)	:	$(OBJS)
		make -C ./mlx_Linux
		$(CC) $(OBJS) -Lmlx_Linux -lmlx_Linux -L/usr/lib -Imlx_Linux -lXext -lX11 -lm -lz -o $@

clean	:
		make -C ./mlx_Linux clean
		rm -rf $(OBJS)

fclean	:	clean
		rm -rf $(NAME)

re	:	fclean
		make all

.PHONY	:	all clean fclean re
