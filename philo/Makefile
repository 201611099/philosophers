# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyojlee <hyojlee@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/09 14:39:28 by hyojlee           #+#    #+#              #
#    Updated: 2022/07/01 19:08:46 by hyojlee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
# CFLAGS = -g3 -fsanitize=address
CFLAGS = -Wall -Wextra -Werror
NAME = philo
SRCS = do_eat.c		\
		do.c		\
		main.c		\
		setting.c	\
		time.c		\
		mutex.c		\
		utils.c
OBJS = $(SRCS:%.c=%.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: clean re fclean all
