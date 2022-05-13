# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/12 22:36:00 by user42            #+#    #+#              #
#    Updated: 2022/05/13 23:16:34 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

SRC		=	main.c \
			philo.c \
			action.c \
			routine.c \


OBJ		=	$(SRC:.c=.o)

CC		=	clang

RM		=	rm -f

CFLAGS		=	-Wall -Wextra -Werror -pthread

CFS			=	-fsanitize=address -g3
#CFS				= -g


all		:	$(NAME)


$(NAME) :	$(OBJ)
			$(CC) $(CFLAGS) -o $(NAME) $(SRC)

%.o:	%.c
	$(CC) -c $(CFLAGS) $(CFS) -o $@ $<

clean	:
			$(RM) $(OBJ)

fclean	:	clean
			$(RM) $(NAME)

norm	:
			norminette $(SRC)
			norminette pipex.h

re		:	fclean all

f 		:	$(OBJ)
			$(CC) $(CFLAGS) $(CFS) -o $(NAME) $(SRC)

fre		:	fclean f

.PHONY : all  clean fclean re f fre norm
