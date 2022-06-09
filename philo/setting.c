/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 21:15:14 by hyojlee           #+#    #+#             */
/*   Updated: 2022/06/09 14:39:53 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
// #include <limits.h>

t_info	*info(void)
{
	static t_info	info;

	return (&info);
}

// NOTE argv 에러처리, argv 값을 t_info에 넣어줌
int	set_info_argv(t_info *info, int argc, char *argv[])
{
	if (argc != 5 && argc != 6)
		return (END);
	info->number_of_philosophers = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->meal_full = ft_atoi(argv[5]);
	return (CONTINUE);
}

// NOTE forks, basetime, anyone_dead, full_list을 초기화 해줌.
int	set_info(t_info *info)
{
	int	i;

	i = 0;
	info->basetime = get_absolute_time();
	info->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* info->number_of_philosophers);
	if (!info->forks)
		return (END);
	if (info->meal_full > 0)
	{
		info->full_list = (int *)malloc(sizeof(int)
				* info->number_of_philosophers);
		if (!info->full_list)
		{
			free(info->forks);
			return (END);
		}
		while (i < info->number_of_philosophers)
			info->full_list[i++] = 0;
	}
	return (CONTINUE);
}

// NOTE (info->forks)포크에 대해서 하나씩 mutex_init 해주고, 
// (info->print_mutex)print에 대해서도 mutex_init 해준다.
int	mutex_init(t_info *info)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&(info->print_mutex), NULL))
	{
		free(info->forks);
		if (info->meal_full)
			free(info->full_list);
		return (END);
	}
	while (i < info->number_of_philosophers)
	{
		if (pthread_mutex_init(&(info->forks[i++]), NULL))
		{
			free(info->forks);
			if (info->meal_full)
				free(info->full_list);
			return (END);
		}
	}
	return (CONTINUE);
}

// NOTE 철학자에 대한 정보 초기화 t_philo에 있는 값들 설정하기 
int	set_philos(t_philo *philos)
{
	unsigned long	init_time;
	int				i;

	i = -1;
	while (++i < info()->number_of_philosophers)
	{
		// t_philo[i]의 멤버 값들 설정하기
		memset(&(philos[i]), 0, sizeof(t_philo));
		philos[i].whoami = i + 1;
		philos[i].left_fork_num = i;
		philos[i].right_fork_num = (i + 1) % info()->number_of_philosophers;
	}
	info()->philos = philos;
	return (CONTINUE);
}
