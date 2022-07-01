/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 21:15:00 by hyojlee           #+#    #+#             */
/*   Updated: 2022/07/01 16:40:56 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

static int	start(t_philo *philos)
{
	int			idx;
	pthread_t	monitor;

	idx = 0;
	if (END == mutex_init())
		return (END);
	while (idx < info()->num_of_philos)
	{
		philos[idx].when_eat = get_relative_time();
		pthread_create(&philos[idx].thread, NULL, philo_do, (void *)&philos[idx]);
		idx++;
	}
	idx = 0;
	if (info()->meal_full > 0)
	{
		pthread_create(&monitor, NULL, monitor_whole, NULL);
		pthread_join(monitor, NULL);
	}
	while (idx < info()->num_of_philos)
		pthread_join(philos[idx++].thread, NULL);
	return (END);
}

int	main(int argc, char *argv[])
{
	t_philo	*philos;

	if (END == set_info_argv(argc, argv))
	{
		printf("error\n");
		return (-1);
	}
	// NOTE Setting
	if (END == set_info())
		return (-1);
	philos = (t_philo *)malloc(sizeof(t_philo) * info()->num_of_philos);
	if (!philos)
		return (free_info(-1));
	set_philos(philos);
	// NOTE Setting

	// NOTE 시작
	start(philos);
	return (free_all(philos));
}
