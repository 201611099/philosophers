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

//한 명의 철학자에 대한 정보가 넘어옴
void	*philo_do(void *param)
{
	t_philo		*philo;
	pthread_t	thread;

	philo = (t_philo *)param;
	pthread_create(&thread, NULL, monitoring, philo);
	// if (!(philo->whoami % 2))
	if ((info()->num_of_philos > 1) && (philo->whoami % 2))
		accurate_sleep(10);
	// NOTE 먹고 자고 생각하고
	while (1)
	{
		// 1. 먹고
		if (eat(philo) == END)
			break ;
		// 2. 자고
		if (doing(SLEEPING, philo) == END)
			break ;
		spend_time_of(SLEEPING);
		// 3. 생각하고
		if (doing(THINKING, philo) == END)
			break;
	}
	pthread_join(thread, NULL);
	return (0);
}

static int	print_doing(t_status status, t_philo *philo)
{
	// NOTE 이 함수에서 printf는 이런 것들이 호출 됬음. 적절한 조건문을 활용하길 바람.
	/*
	printf("is eating\n");
	printf("is sleeping\n");
	printf("is thinking\n");
	printf("has taken a fork\n");
	printf("has taken a fork\n");
	printf("is died\n");
	*/
	if (status == EATING)
		printf("\x1b[34m%d is eating.\n\x1b[0m", philo->whoami);
	else if (status == SLEEPING)
		printf("\x1b[32m%d is sleeping.\n\x1b[0m", philo->whoami);
	else if (status == THINKING)
		printf("\x1b[33m%d is thinking.\n\x1b[0m", philo->whoami);
	else if (status == LEFT_TAKEN)
		printf("%d has taken a left fork.\n", philo->whoami);
	else if (status == RIGHT_TAKEN)
		printf("%d has taken a right fork.\n", philo->whoami);
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

