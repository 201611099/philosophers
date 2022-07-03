/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_eat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 21:00:55 by hyojlee           #+#    #+#             */
/*   Updated: 2022/07/02 21:52:41 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	forks_mutex_lock(t_philo *philo)
{
	pthread_mutex_lock(&(info()->forks[philo->left_fork_num]));
	if (doing(LEFT_TAKEN, philo) == END)
	{
		pthread_mutex_unlock(&(info()->forks[philo->left_fork_num]));
		return (END);
	}
	pthread_mutex_lock(&(info()->forks[philo->right_fork_num]));
	if (doing(RIGHT_TAKEN, philo) == END)
	{
		pthread_mutex_unlock(&(info()->forks[philo->left_fork_num]));
		pthread_mutex_unlock(&(info()->forks[philo->right_fork_num]));
		return (END);
	}
	if (doing(EATING, philo) == END)
	{
		pthread_mutex_unlock(&(info()->forks[philo->left_fork_num]));
		pthread_mutex_unlock(&(info()->forks[philo->right_fork_num]));
		return (END);
	}
	return (CONTINUE);
}

int	eat(t_philo *philo)
{
	if (info()->anyone_dead)
		return (END);
	if (END == forks_mutex_lock(philo))
		return (END);
	spend_time_of(EATING);
	philo->meal_num++;
	if (info()->num_of_meals > 0 && philo->meal_num == info()->num_of_meals)
		info()->full_list[philo->whoami - 1] = 1;
	pthread_mutex_unlock(&(info()->forks[philo->left_fork_num]));
	pthread_mutex_unlock(&(info()->forks[philo->right_fork_num]));
	return (CONTINUE);
}
