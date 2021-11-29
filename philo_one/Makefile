CC = gcc
#CFLAGS = -Wall -Wextra -Werror
CFLAGS = -fsanitize=address -g3
NAME = philo_one
SRCS = do_eat.c do.c main.c setting.c time.c \
		ft_atoi.c
OBJS = $(SRCS:%.c=%.o)

all : $(NAME)

%.o : %.c
	$(CC) -c $< -o $@

$(NAME) :
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME);
	
test : 
	$(CC) $(CFLAGS) $(SRCS);

clean :
	rm -f $(NAME)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: clean bonus re fclean all