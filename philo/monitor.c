/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 20:56:21 by hyojlee           #+#    #+#             */
/*   Updated: 2022/07/02 21:54:02 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_all_philos_full(void)
{
	int	idx;
	
	idx = 0;
	if (info()->num_of_meals == 0)
		return (FALSE);
	while (info()->num_of_meals > 0 && idx < info()->num_of_philos)
	{
		if (info()->full_list[idx] == 0)
			break ;
		idx++;
	}
	if (idx == info()->num_of_philos)
	{
		// info()->anyone_dead = TRUE;
		// printf("\x1b[35mEnd of meal\n\x1b[0m");
		// doing(MEAL, philo, get_relative_time());
		return (TRUE);
	}
	return (FALSE);
}

void	*monitor_whole(void *param)
{
	param = NULL;
	while (1)
	{
		if (info()->anyone_dead == TRUE)
			break ;
		if (is_all_philos_full() == TRUE)
		{
			info()->anyone_dead = TRUE;
			pthread_mutex_lock(&(info()->print_mutex));
			printf("\x1b[35m%lums End of meal\n\x1b[0m", get_relative_time());
			pthread_mutex_unlock(&(info()->print_mutex));
			break ;
		}
	}
	return (0);
}

// 하나의 철학자에 대한 모니터링
void	*monitoring(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	
	while (1)
	{
		// NOTE 확인해야하는 것
		// 1. 어느 한명이라도 죽었다면, break; (내가 아니더라도, 누군가 죽었으면 Stop!)
		if (info()->anyone_dead == TRUE)
			return (0);
		// 2. 인자가 주어진 경우 모든 철학자가 밥을 먹었으면, break;

		// 3. 시간 계산을 해서, 현재 이 모니터함수가 관찰하고 있는 철학자가 죽었다면, dead 출력 후 break;
		if (philo->when_eat + info()->time_to_die < get_relative_time())
		{
			doing(DEAD, philo);
			if (2 > info()->num_of_philos)
				pthread_mutex_unlock(&(info()->forks[philo->left_fork_num]));
			return (0);
		}
		accurate_sleep(2);
	}
}
