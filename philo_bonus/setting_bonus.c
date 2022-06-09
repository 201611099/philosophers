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

#include "philo_bonus.h"
#include <limits.h>

t_info	*info(void)
{
	static t_info	info;

	return (&info);
}

// NOTE forks, basetime, anyone_dead, full_list을 초기화 해줌.
int	set_info(t_info *info)
{
	int		i;
	int		flag;
	char	*name;

	i = 0;
	flag = O_CREAT | O_EXCL;
	info->basetime = get_absolute_time();
	sem_unlink_all();
	sem_unlink_full_list(info->number_of_philosophers);
	info->forks = sem_open("/sem_forks", flag, 0755, info->number_of_philosophers);
	info->print_sem = sem_open("/sem_print", flag, 0755, 1);
	info->eat_people = sem_open("/sem_eat", flag, 0755, info->number_of_philosophers / 2);
	if (info->forks == SEM_FAILED || info->forks == SEM_FAILED || info->forks == SEM_FAILED)
	{
		return (sem_close_all(info));
	}
	if (info->meal_full > 0)
	{
		info->full_list = (sem_t **)malloc(sizeof(sem_t *)
				* info->number_of_philosophers);
		if (!info->full_list)
		{
			return (sem_close_all(info));
		}
		while (i < info->number_of_philosophers)
		{
			// ft_itoa를 받아주는 char* 필요할꺼같은데, 안그럼 메모리누수 날꺼같음.
			name = ft_itoa(i);
			info->full_list[i] = sem_open(name, flag, 0755, 1);
			free(name);
			if (info->full_list[i] == SEM_FAILED)
			{
				sem_close_full_list(i);
				free(info->full_list);
				return (sem_close_all(info));
			}
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
	}
	info()->philos = philos;
	return (CONTINUE);
}

// 만약을 위해서 남겨둠!! 쓰진 않는데
int deprecated_semopen(t_info *info)
{
	int flag;

	flag = O_CREAT | O_EXCL;
	info->forks = sem_open("/sem_forks", flag, 0755, info->number_of_philosophers);
	if (info->forks == SEM_FAILED)
		return (END);
	info->print_sem = sem_open("/sem_print", flag, 0755, 1);
	if (info->print_sem == SEM_FAILED)
	{
		sem_close(info->forks);
		return (END);
	}
	info->eat_people = sem_open("/sem_eat", flag, 0755, info->number_of_philosophers / 2);
	if (info->eat_people == SEM_FAILED)
	{
		sem_close(info->forks);
		sem_close(info->print_sem);
		return (END);
	}
	return (CONTINUE);
}