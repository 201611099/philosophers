/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 21:15:14 by yunslee           #+#    #+#             */
/*   Updated: 2021/03/09 01:08:01 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

// NOTE argv 에러처리, argv 값을 t_info에 넣어줌
int		set_info_argv(t_info *info, int argc, char *argv[])
{
	if (argc != 5 && argc != 6)
		return (-1);

	info->number_of_philosophers = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
}

// set_info에 있는거 여기서 초기화해줘도 됨 
// NOTE forks, basetime, anyone_dead, full_list을 초기화 해줌.
int		set_info(t_info *info)
{
	info->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * g_philo_num);
	info->basetime = get_absolute_time();
	info->anyone_dead = FALSE;
	info->full_list = NULL; // 인자값 들어올 때는 수정
}

// NOTE (info->forks)포크에 대해서 하나씩 mutex_init 해주고, (info->print_mutex)print에 대해서도 mutex_init 해준다.
void	mutex_init(t_info *info)
{
	int i;

	i = -1;
	pthread_mutex_init(&(info->print_mutex), NULL);
	while (++i < info->number_of_philosophers)
		pthread_mutex_init(&(info->forks[i]), NULL);
}


// NOTE 철학자에 대한 정보 초기화 t_philo에 있는 값들 설정하기 
int		set_philos(t_philo *philos)
{
	unsigned long	init_time;
	int				i;

	i = 0;
	while (i < g_philo_num)
	{
		memset(&(philos[i]), 0, sizeof(t_philo));
		philos[i].whoami = i + 1;
		philos[i].left_fork_num = i;
		philos[i].right_fork_num = (i + 1) % g_philo_num;
		//printf("philo, left, right: %d %d %d\n", philos[i].whoami, philos[i].left_fork_num, philos[i].right_fork_num);
		// t_philo[i]의 멤버 값들 설정하기
		i++;
	}
	return (1);
}
