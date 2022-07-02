/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 21:15:00 by hyojlee           #+#    #+#             */
/*   Updated: 2022/07/02 22:28:00 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (info()->num_of_meals > 0)
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
	int		chk_arg;

	chk_arg = set_info_argv(argc, argv);
	if (CONTINUE != chk_arg)
		return (chk_arg);
	// NOTE Setting
	if (END == set_info())
	{
		printf("error\n");
		return (ERROR);
	}
	philos = (t_philo *)malloc(sizeof(t_philo) * info()->num_of_philos);
	if (!philos)
		return (free_info(-1));
	set_philos(philos);
	// NOTE Setting

	// NOTE 시작
	start(philos);
	return (free_all(philos));
}
