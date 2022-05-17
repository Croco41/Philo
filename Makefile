# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/12 22:36:00 by user42            #+#    #+#              #
#    Updated: 2022/05/17 13:23:25 by cgranja          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

SRC		=	main.c \
			philo.c \
			actions.c \
			routine.c \
			clean.c \
			utils/ft_atoi.c \
			utils/ft_putnbr.c \
			utils/ft_putstr.c \

OBJ		=	$(SRC:.c=.o)

CC		=	clang

RM		=	rm -f

CFLAGS		=	-Wall -Wextra -Werror -pthread

#CFS			=	-fsanitize=address -g3
#CFS				= -fsanitize=thread


all		:	$(NAME)


$(NAME) :	$(OBJ)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o:	%.c
	$(CC) -o $@ -c  $< $(CFLAGS) $(CFS)

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
