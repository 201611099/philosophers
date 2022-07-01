/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:45:35 by hyojlee           #+#    #+#             */
/*   Updated: 2022/07/01 16:56:15 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

// NOTE (info->forks)포크에 대해서 하나씩 mutex_init 해주고, 
// (info->print_mutex)print에 대해서도 mutex_init 해준다.
int	mutex_init(void)
{
	int	idx;

	idx = 0;
	if (pthread_mutex_init(&(info()->print_mutex), NULL))
		return (free_info(END));
	while (idx < info()->num_of_philos)
	{
		if (pthread_mutex_init(&(info()->forks[idx++]), NULL))
		{
			mutex_destroy(idx - 1);
			return (free_info(END));
		}
	}
	return (CONTINUE);
}

void	mutex_destroy(int num_of_forks)
{
	int	idx;

	idx = 0;
	pthread_mutex_destroy(&(info()->print_mutex));
	while (idx < num_of_forks)
		pthread_mutex_destroy(&(info()->forks[idx++]));
}