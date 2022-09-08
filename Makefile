# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccottin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/02 17:05:58 by ccottin           #+#    #+#              #
#    Updated: 2022/09/08 17:42:39 by ybendavi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D

SRCS	= init_map.c utils.c init.c ft_return.c main.c\
	set_info.c get_info_wall.c utils1.c set_info_map.c\
	raycaster.c events_handler.c key_handler.c\
	key_handler_p2.c init_player.c initcaster.c texture.c\
	init_map_utils.c ft_cub3d.c map_closed.c

SRCSDIR	= srcs

OBJSDIR	= objs

OBJS	= ${SRCS:%.c=${OBJSDIR}/%.o}

CC	= gcc

CFLAGS	= -Wall -Wextra -Werror -g3 

all	:	$(NAME)


$(NAME)	:	$(OBJS)
		make -C ./mlx_Linux
		$(CC) $(OBJS) -Lmlx_Linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz -o ${NAME}

${OBJS} :	${OBJSDIR}/%.o: ${SRCSDIR}/%.c
		mkdir -p ${OBJSDIR}
		$(CC) $(CFLAGS) -Iincludes -Imlx_Linux -c $< -o $@

clean	:
		make -C ./mlx_Linux clean
		rm -rf $(OBJS)
		rm -rf $(OBJSDIR)

fclean	:	clean
		rm -rf $(NAME)

re	:	fclean
		make all

.PHONY	:	all clean fclean re
