/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 21:15:14 by hyojlee           #+#    #+#             */
/*   Updated: 2022/07/02 22:25:34 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
// #include <limits.h>

t_info	*info(void)
{
	static t_info	info;

	return (&info);
}

static int valid_arg(int argc, int error)
{
	if (ERROR == error)
	{
		printf("error: invalid argument\n");
		return (ERROR);
	}
	if (info()->num_of_philos < 0 || info()->time_to_die < 0
		|| info()->time_to_eat < 0 || info()->time_to_sleep < 0)
	{
		printf("error: invalid argument\n");
		return (ERROR);
	}
	if (6 == argc)
	{
		if (info()->num_of_meals < 0)
			return (ERROR);
		else if (info()->num_of_meals == 0)
			return (END);
	}
	return (CONTINUE);
}

// NOTE argv 에러처리, argv 값을 t_info에 넣어줌
int	set_info_argv(int argc, char *argv[])
{
	int	error;

	error = 0;
	if (argc < 5 || argc > 6)
	{
		printf("error: invalid argument\n");
		return (ERROR);
	}
	info()->num_of_philos = ft_atoi(argv[1], &error);
	info()->time_to_die = ft_atoi(argv[2], &error);
	info()->time_to_eat = ft_atoi(argv[3], &error);
	info()->time_to_sleep = ft_atoi(argv[4], &error);
	if (argc == 6)
		info()->num_of_meals = ft_atoi(argv[5], &error);
	return (valid_arg(argc, error));
}

// NOTE forks, basetime, anyone_dead, full_list을 초기화 해줌.
int	set_info(void)
{
	int	i;

	i = 0;
	info()->basetime = get_absolute_time();
	info()->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* info()->num_of_philos);
	if (!info()->forks)
		return (END);
	if (info()->num_of_meals > 0)
	{
		info()->full_list = (int *)malloc(sizeof(int) * info()->num_of_philos);
		if (!info()->full_list)
		{
			free(info()->forks);
			return (END);
		}
		while (i < info()->num_of_philos)
			info()->full_list[i++] = 0;
	}
	return (CONTINUE);
}

// NOTE 철학자에 대한 정보 초기화 t_philo에 있는 값들 설정하기 
int	set_philos(t_philo *philos)
{
	int	idx;

	idx = -1;
	while (++idx < info()->num_of_philos)
	{
		// t_philo[i]의 멤버 값들 설정하기
		memset(&(philos[idx]), 0, sizeof(t_philo));
		philos[idx].whoami = idx + 1;
		philos[idx].left_fork_num = idx;
		philos[idx].right_fork_num = (idx + 1) % info()->num_of_philos;
	}
	info()->philos = philos;
	return (CONTINUE);
}
