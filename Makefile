# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elias <elias@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/29 19:25:41 by emoreau           #+#    #+#              #
#    Updated: 2023/09/26 17:23:32 by elias            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR		= ./srcs/
OBJ_DIR	= ./obj/
SRCS	=	philo.c\

OBJS = $(patsubst %.c,$(OBJ_DIR)%.o,$(SRCS))

NAME	=	philo
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g3
RM		=	rm -rf

all:	${NAME}

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	${RM} $(OBJ_DIR)

fclean:	clean
		${RM} ${NAME}

re:		fclean all

.PHONY: 	all clean fclean re