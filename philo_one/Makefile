CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = philo_one
SRCS = do_eat.c do.c main.c setting.c time.c \
		ft_atoi.c
# OBJS = $(SRCS:%.c=%.o)

all : $(NAME)
# %.o : %.c
# 	$(CC) -c $< -o $@
$(NAME) :
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME);
	
.PHONY: clean bonus re fclean all

clean :
	rm -f $(NAME)
fclean : clean
	rm -f $(NAME)
re : fclean all
