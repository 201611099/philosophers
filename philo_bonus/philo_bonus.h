/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 21:10:20 by hyojlee           #+#    #+#             */
/*   Updated: 2022/06/09 14:39:53 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdbool.h>
# include <signal.h>

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

typedef struct	s_philo
{
	pid_t			pid;
	int				whoami; //몇 번째 철학자인가
	unsigned long	when_eat;
	int				meal_num;
}				t_philo;

typedef struct	s_info
{
	int				number_of_philosophers;
	unsigned long	time_to_die; //set_info_argv
	int				time_to_eat; //set_info_argv
	int				time_to_sleep; //set_info_argv
	int				meal_full; //set_info_argv
	unsigned long	basetime; //set_info
	sem_t			*forks; // #(philos)
	sem_t			*print_sem; // #1
	sem_t			*eat_people; // #(philos) / 2
	//누군가 다 먹었다. 부모에게 알려야 한다. #(philos)
	sem_t			**full_list; //다 먹은 철학자 판별해주는 역할(?)
	t_philo			*philos; //main
}				t_info;


int				g_philo_num;

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
t_info			*info(void);
int				set_info_argv(t_info *info, int argc, char *argv[]);
void			mutex_fork_init(t_info *info); //존재하지 않음.
int				mutex_init(t_info *info);
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
void			*philo_do(t_philo *philo);
int				print_doing(t_status status, t_philo *philo);
int				is_all_philos_full();
// int				is_all_philos_full(t_philo *philo);


/*
** do_eat.c
*/
int				eat(t_philo *philo, t_info *info);

/*
** ft_itoa.c
*/
char			*ft_itoa(int n);

/*
** clear.c
*/
void			sem_unlink_all();
void			sem_unlink_full_list(int n);
int				sem_close_all(t_info *info);
int				sem_close_full_list(int n);
int				set_info_argv(t_info *info, int argc, char *argv[]);

#endif
