/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 21:15:00 by yunslee           #+#    #+#             */
/*   Updated: 2021/03/09 01:08:50 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		start(t_philo *philos, t_info *info)
{
	int i;

	i = 0;
	mutex_init(info);
	while (i < g_philo_num)
	{
		philos[i].when_eat = get_relative_time();
		pthread_create(&philos[i].thread, NULL, philo_do, (void *)&philos[i]);
		i++;
	}
	i = 0;
	while (i < g_philo_num)
		pthread_join(philos[i++].thread, NULL);
	return (CONTINUE);
}

int		main(int argc, char *argv[])
{
	t_philo	*philos;

	if (-1 == set_info_argv(&g_info, argc, argv))
	{
		printf("error\n");
		return (-1);
	}
	// NOTE Setting
	set_info(&g_info);
	g_philo_num = g_info.number_of_philosophers;
	philos = malloc(sizeof(t_philo) * g_philo_num);
	set_philos(philos);
	// NOTE Setting

	// NOTE 시작
	start(philos, &g_info);
	free_all(philos);
	return (0);
}

void	free_all(t_philo *philos)
{
	free(philos);
	free(g_info.forks);
	free(g_info.full_list);
}
