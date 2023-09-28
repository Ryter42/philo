# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/29 19:25:41 by emoreau           #+#    #+#              #
#    Updated: 2023/09/28 21:38:02 by emoreau          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR		= ./srcs/
OBJ_DIR	= ./obj/
SRCS	=	philo.c\
			init.c\
			utils.c\
			free.c

OBJS = $(patsubst %.c,$(OBJ_DIR)%.o,$(SRCS))

NAME	=	philo
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g3 -fsanitize=thread
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