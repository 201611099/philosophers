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
		return (TRUE);
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

void	*monitoring(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	while (1)
	{
		if (info()->anyone_dead == TRUE)
			return (0);
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
