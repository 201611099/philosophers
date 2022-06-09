# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/09 14:39:23 by hyojlee           #+#    #+#              #
#    Updated: 2022/06/09 14:41:47 by hyojlee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
# CFLAGS = -g3 -fsanitize=address
CFLAGS = -Wall -Wextra -Werror
NAME = philo_bonus
SRCS = do_eat_bonus.c	\
		do_bonus.c		\
		main_bonus.c	\
		setting_bonus.c	\
		time_bonus.c	\
		ft_atoi_bonus.c
OBJS = $(SRCS:%.c=%.o)

all : $(NAME)

%.o : %.c
	$(CC) -c $< -o $@

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: clean re fclean all
