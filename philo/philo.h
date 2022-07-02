/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 21:10:20 by hyojlee           #+#    #+#             */
/*   Updated: 2022/07/02 22:23:39 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <stdio.h>
# include <stdbool.h>

# define FALSE 0
# define TRUE 1
# define END 0
# define CONTINUE 1
# define ERROR -1
# define INT_MAX 2147483647
# define INT_MIN -2147483648

typedef enum
{
	EATING = 0,
	SLEEPING,
	THINKING,
	LEFT_TAKEN,
	RIGHT_TAKEN,
	DEAD
}	t_status;

// struct s_info;

typedef struct	s_philo
{
	pthread_t		thread;
	int				whoami;
	unsigned long	when_eat;
	int				left_fork_num;
	int				right_fork_num;
	int				meal_num;
	//struct s_info	*info;
}				t_philo;

typedef struct	s_info
{
	int				num_of_philos;
	unsigned long	time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_meals;
	unsigned long	basetime;
	int				anyone_dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	int				*full_list; //다 먹은 철학자 판별해주는 역할(?)
	t_philo			*philos;
}				t_info;

/*
** main.c
*/
int				main(int argc, char *argv[]);

/*
** setting.c
*/
t_info			*info(void);
int				set_info_argv(int argc, char *argv[]);
int				set_info(void);
int				set_philos(t_philo *philos);

/*
** time.c
*/
unsigned long	get_relative_time();
unsigned long	get_absolute_time();
int				spend_time_of(t_status doing);
void			accurate_sleep(unsigned long milisecond);

/*
** do.c
*/
void			*philo_do(void *param);
int				doing(t_status status, t_philo *philo);

/*
** do_eat.c
*/
int				eat(t_philo *philo);

/*
** utils.c
*/
int				ft_atoi(char *str, int *err);
int				free_info(int ret);
int				free_all(t_philo *philo);

/*
** mutex.c
*/
int				mutex_init(void);
void			mutex_destroy(int fork_idx);

/*
** monitor.c
*/
void			*monitor_whole(void *param);
void			*monitoring(void *param);

#endif
