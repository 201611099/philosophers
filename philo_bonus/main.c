/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 21:15:00 by yunslee           #+#    #+#             */
/*   Updated: 2021/12/19 20:34:24 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitoring_whole(t_info	*info)
{
	while (1)
	{
		if (info->anyone_dead == TRUE) // 누군가 죽었다면, 프로세스 종료
			break ;
		if (is_all_philos_full() == TRUE) // 모두가 다 먹었다면, 프로세스 종료
		{
			break ;
		}
	}
	return (0);
}

// start()는 확실히 이 포맷을 따라가는 것이 좋아 보임 12.19(yunslee)
int	start(t_philo *philos, t_info *info)
{
	int		i;
	int		status;
	pid_t	pid;
	
	i = 0;
	while (i < g_philo_num)
	{
		philos[i].pid = fork();
		if (philos[i].pid == 0)
			break;
		i++;
	}
	if (i != g_philo_num)
		philo_do(&philos[i]);
	else
		monitoring_whole(info);
	return (CONTINUE);
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
	philos = (t_philo *)malloc(sizeof(t_philo) * g_philo_num);
	if (!philos)
	{
		sem_close_all(info());
		sem_close_full_list(info()->number_of_philosophers);
		return (-1);
	}
	// NOTE Setting

	// NOTE 시작
	start(philos, info());
	free_all(philos);
	return (0);
}
