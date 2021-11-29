/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 21:01:14 by yunslee           #+#    #+#             */
/*   Updated: 2021/03/16 05:55:40 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		print_doing(t_status status, t_philo *philo)
{
	// NOTE 이 함수에서 printf는 이런 것들이 호출 됬음. 적절한 조건문을 활용하길 바람.
	if (status == EATING)
		printf("%d is eating.\n", philo->whoami);
	else if (status == SLEEPING)
		printf("%d is sleeping.\n", philo->whoami);
	else if (status == THINKING)
		printf("%d is thinking.\n", philo->whoami);
	else if (status == LEFT_TAKEN)
		printf("%d has taken left fork.\n", philo->whoami);
	else if (status == RIGHT_TAKEN)
		printf("%d has taken right fork.\n", philo->whoami);
	else if (status == DEAD)
	{
		printf("%d is dead.\n", philo->whoami);
		return (END);
	}
	return (CONTINUE);
}

int		doing(t_status status, t_philo *philo, unsigned long interval)
{
	int	ret;

	if (status == EATING)
	{
		eat(philo, &g_info);
	}
	pthread_mutex_lock(&(g_info.print_mutex));
	printf("[%lu] ", get_relative_time());
	// printf("[%lu] ", interval);
	ret = print_doing(status, philo);
	pthread_mutex_unlock(&(g_info.print_mutex));
	if (status == EATING || status == SLEEPING)
	{
		spend_time_of(status);
		if (status == EATING)
		{
			pthread_mutex_unlock(&(g_info.forks[philo->left_fork_num]));
			// printf("\x1b[31m %d  eat start! - put left fork(%d)\n\x1b[0m", philo->whoami, philo->left_fork_num);
			pthread_mutex_unlock(&(g_info.forks[philo->right_fork_num]));
			// printf("\x1b[31m %d  eat start! - put right fork(%d)\n\x1b[0m", philo->whoami, philo->right_fork_num);
		}
	}
	
	// NOTE 출력에 대해서 mutex를 해줘야 출력이 안 꼬임. 출력하는 순간을 동기화하는 것임
	//
	///*
	//먹고, 자고, 죽고
	//누군가 죽고, 다 먹었고, etc...
	//모든 출력은 이 안에서, 그리고 아래 있는 함수 print_doing() 에서 일어남.
	//// TODO Hnt
	//ret = print_doing(t_status status, t_philo *philo)
	//*/
	//
	// NOTE 출력에 대해서 mutex를 해줘야 출력이 안 꼬임. 출력하는 순간을 동기화하는 것임

	// NOTE 상태에 따라서 philo_do의 while(1)을 나갈 수 있게 함.(exit()을 쓰는 것이 편할지 모르지만, 안 써도 충분히 가능함.)
	if (ret == CONTINUE)
		return (CONTINUE);
	else if (ret == END)
		return (END);
	return (END);
}

bool	is_all_philos_full(void)
{
}

void	*monitoring(void *param)
{
	t_philo			*philo;
	unsigned long	time;

	philo = (t_philo *)param;
	
	while (1)
	{
		// NOTE 확인해야하는 것
		// 1. 어느 한명이라도 죽었다면, break; (내가 아니더라도, 누군가 죽었으면 Stop!)
		if (g_info.anyone_dead)
			break ;
		// 2. 인자가 주어진 경우 모든 철학자가 밥을 먹었으면, break;
		// 3. 시간 계산을 해서, 현재 이 모니터함수가 관찰하고 있는 철학자가 죽었다면, dead 출력 후 break;
		if (get_relative_time() > g_info.time_to_die + philo->when_eat)
		{
			g_info.anyone_dead = true;
			break;
		}
	}
	return (NULL);
}

void	*philo_do(void *param)
{
	t_philo		*philo;
	pthread_t	thread;

	philo = (t_philo *)param;
	pthread_create(&thread, NULL, monitoring, philo);
	//
	//
	if (philo->whoami % 2 == 0)
		accurate_sleep(5);
	// NOTE 먹고 자고 생각하고
	while (1)
	{
		#pragma region yunslee
		if (doing(EATING, philo, get_relative_time()) == END)
		{
			doing(DEAD, philo, get_relative_time());
			break;
		}

		if (doing(SLEEPING, philo, get_relative_time()) == END)
		{
			doing(DEAD, philo, get_relative_time());
			break;
		}

		if (doing(THINKING, philo, get_relative_time()) == END)
		{
			doing(DEAD, philo, get_relative_time());
			break;
		}
		#pragma endregion

		// 1. 먹고
		// 2. 자고
		// 3. 생각하고
	}
	pthread_join(thread, NULL);
	return (NULL);
}
