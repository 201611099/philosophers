/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 21:15:00 by yunslee           #+#    #+#             */
/*   Updated: 2021/12/19 14:13:03 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_whole(void *param)
{
	t_info	*info;

	info = (t_info *)param;
	while (1)
	{
		if (info->anyone_dead == TRUE)
			break ;
		if (is_all_philos_full() == TRUE)
		{
			info->anyone_dead = TRUE;
			pthread_mutex_lock(&(info->print_mutex));
			printf("\x1b[35m%lums End of meal\n\x1b[0m", get_relative_time());
			pthread_mutex_unlock(&(info->print_mutex));
			break ;
		}
	}
	return (0);
}

int	start(t_philo *philos, t_info *info)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	if (mutex_init(info) == END)
		return (END);
	while (i < g_philo_num)
	{
		philos[i].when_eat = get_relative_time();
		pthread_create(&philos[i].thread, NULL, philo_do, (void *)&philos[i]);
		i++;
	}
	i = 0;
	if (info->meal_full > 0)
	{
		pthread_create(&monitor, NULL, monitor_whole, info);
		pthread_join(monitor, NULL);
	}
	while (i < g_philo_num)
		pthread_join(philos[i++].thread, NULL);
	return (END);
}

int	main(int argc, char *argv[])
{
	t_philo	*philos;

	if (-1 == set_info_argv(info(), argc, argv))
	{
		printf("error\n");
		return (-1);
	}
	// NOTE Setting
	if (set_info(info()) == END)
		return (-1);
	g_philo_num = info()->number_of_philosophers;
	philos = malloc(sizeof(t_philo) * g_philo_num);
	set_philos(philos);
	// NOTE Setting

	// NOTE 시작
	start(philos, info());
	free_all(philos);
	return (0);
}

void	free_all(t_philo *philos)
{
	free(philos);
	free(info()->forks);
	if (info()->meal_full)
		free(info()->full_list);
}
