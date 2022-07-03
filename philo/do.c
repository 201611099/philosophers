/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 21:01:14 by hyojlee           #+#    #+#             */
/*   Updated: 2022/07/02 21:33:50 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_do(void *param)
{
	t_philo		*philo;
	pthread_t	thread;

	philo = (t_philo *)param;
	pthread_create(&thread, NULL, monitoring, philo);
	if ((info()->num_of_philos > 1) && (philo->whoami % 2))
		accurate_sleep(10);
	while (1)
	{
		if (eat(philo) == END)
			break ;
		if (doing(SLEEPING, philo) == END)
			break ;
		spend_time_of(SLEEPING);
		if (doing(THINKING, philo) == END)
			break ;
	}
	pthread_join(thread, NULL);
	return (0);
}

static int	print_doing(t_status status, t_philo *philo)
{
	if (status == EATING)
		printf("\x1b[34m%d is eating.\n\x1b[0m", philo->whoami);
	else if (status == SLEEPING)
		printf("\x1b[32m%d is sleeping.\n\x1b[0m", philo->whoami);
	else if (status == THINKING)
		printf("\x1b[33m%d is thinking.\n\x1b[0m", philo->whoami);
	else if (status == LEFT_TAKEN)
		printf("%d has taken a fork.\n", philo->whoami);
	else if (status == RIGHT_TAKEN)
		printf("%d has taken a fork.\n", philo->whoami);
	else if (status == DEAD)
	{
		printf("\x1b[31m%d died.\n\x1b[0m", philo->whoami);
		info()->anyone_dead = TRUE;
		return (END);
	}
	return (CONTINUE);
}

int	doing(t_status status, t_philo *philo)
{
	int				ret;
	unsigned long	times;

	if (info()->anyone_dead == TRUE)
		return (END);
	pthread_mutex_lock(&(info()->print_mutex));
	times = get_relative_time();
	if (info()->anyone_dead == FALSE)
	{
		if (status == EATING)
			philo->when_eat = times;
		printf("%lums ", times);
		ret = print_doing(status, philo);
	}
	else
		ret = END;
	pthread_mutex_unlock(&(info()->print_mutex));
	return (ret);
}
