/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 21:10:20 by yunslee           #+#    #+#             */
/*   Updated: 2021/03/09 01:08:06 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdbool.h>

# define FALSE 0
# define TRUE 1
# define END 0
# define CONTINUE 1

typedef enum
{
	EATING = 0,
	SLEEPING,
	THINKING,
	LEFT_TAKEN,
	RIGHT_TAKEN,
	DEAD
}	t_status;

typedef struct	s_info
{
	int				number_of_philosophers;
	unsigned long	time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_full;
	unsigned long	basetime;
	bool			anyone_dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	char			*full_list;
}				t_info;

typedef struct	s_philo
{
	pthread_t		thread;
	int				whoami;
	unsigned long	when_eat;
	int				left_fork_num;
	int				right_fork_num;
	int				meal_num;
}				t_philo;

int				g_philo_num;
t_info			g_info;

/*
** main.c
*/
int				start(t_philo *philos, t_info *info);
int				main(int argc, char *argv[]);
void			*test(void *param);
void			free_all(t_philo *philos);

/*
** setting.c
*/
int				set_info_argv(t_info *info, int argc, char *argv[]);
void			mutex_fork_init(t_info *info);
void			mutex_init(t_info *info);
void			print_info(t_info *info);
int				set_info(t_info *info);
int				set_philos(t_philo *philos);

/*
** ft_atoi.c
*/
int				ft_atoi(const char *str);

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
int				eat(t_philo *philo, t_info *info);
void			*monitoring(void *param);
int				doing(t_status status, t_philo *philo, unsigned long interval);
void			*philo_do(void *param);
int				print_doing(t_status status, t_philo *philo);
bool			is_all_philos_full();

/*
** do_eat.c
*/
int				eat_one_direction(t_philo *philo, t_info *info);
int				eat(t_philo *philo, t_info *info);
#endif
