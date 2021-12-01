CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = philo_one
SRCS = do_eat.c do.c main.c setting.c time.c \
		ft_atoi.c
OBJS = $(SRCS:%.c=%.o)

all : $(NAME)

%.o : %.c
	$(CC) -c $< -o $@

$(NAME) : $(OBJS)
	$(CC) $(OBJS) -o $(NAME);
#	$(CC) $(CFLAGS) $(OBJS) -o $(NAME);
	
clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: clean bonus re fclean all
