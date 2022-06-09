/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 21:01:14 by hyojlee           #+#    #+#             */
/*   Updated: 2022/06/09 14:39:53 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int		print_doing(t_status status, t_philo *philo)
{
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

int		doing(t_status status, t_philo *philo, unsigned long interval)
{
	int				ret;
	unsigned long	times;

	// times = interval;
	if (info()->anyone_dead == TRUE)
		return (END);
	sem_wait(info()->print_sem);
	//pthread_mutex_lock(&(info()->print_mutex));
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
	//pthread_mutex_unlock(&(info()->print_mutex));
	sem_post(info()->print_sem);
	return (ret);
}

int	is_all_philos_full()
{
	int i;
	
	i = 0;
	if (info()->meal_full == 0)
		return (FALSE);
	while (info()->meal_full > 0 && i < info()->number_of_philosophers)
	{
		if (info()->full_list[i] == 0)
			break ;
		i++;
	}
	if (i == info()->number_of_philosophers)
	{
		// info()->anyone_dead = TRUE;
		// printf("\x1b[35mEnd of meal\n\x1b[0m");
		// doing(MEAL, philo, get_relative_time());
		return (TRUE);
	}
	return (FALSE);
}

// 하나의 철학자에 대한 모니터링
void	*monitoring(void *param)
{
	t_philo			*philo;
	unsigned long	time;

	philo = (t_philo *)param;
	
	while (1)
	{
		// 1. 어느 한명이라도 죽었다면, monitoring_whole 에서 철학자를 죽일 것 같음. 따라서 여기서는 필요 없을 듯
		// 2. 인자가 주어진 경우 모든 철학자가 밥을 먹었으면, break, sem_post
		// 3. 시간 계산을 해서, 현재 이 모니터함수가 관찰하고 있는 철학자가 죽었다면, dead 출력 후, exit();
		if (philo->when_eat + info()->time_to_die < get_relative_time())
		{
			doing(DEAD, philo, get_relative_time());
			return (0);
		}
		accurate_sleep(3);
	}
}

//한 명의 철학자에 대한 정보가 넘어옴
void	*philo_do(t_philo	*philo)
{
	pthread_t	thread;

	//philo = (t_philo *)param;
	pthread_create(&thread, NULL, monitoring, philo);

	if (philo->whoami % 2)
		accurate_sleep(3);
	// NOTE 먹고 자고 생각하고
	while (1)
	{
		// 1. 먹고
		if (eat(philo, info()) == END)
			break ;
		// 2. 자고
		if (doing(SLEEPING, philo, get_relative_time()) == END)
			break ;
		spend_time_of(SLEEPING);
		// 3. 생각하고
		if (doing(THINKING, philo, get_relative_time()) == END)
			break;
	}
	pthread_join(thread, NULL);
	return (0);
}
