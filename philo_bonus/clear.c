/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 21:00:55 by yunslee           #+#    #+#             */
/*   Updated: 2021/12/19 20:39:20 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	sem_close_all(t_info *info)
{
	sem_close(info->forks);
	sem_close(info->print_sem);
	sem_close(info->eat_people);
	return (END);
}

int	sem_close_full_list(int n)
{
	int		i;
	char	*name;

	i = 0;
	while (i < n)
	{
		name = ft_itoa(i);
		sem_close(name);
		free(name);
		i++;
	}
	return (END);
}

void	sem_unlink_full_list(int n)
{
	int		i;
	char	*name;

	i = 0;
	while (i < n)
	{
		name = ft_itoa(i);
		sem_unlink(name);
		free(name);
		i++;
	}
}

void		sem_unlink_all()
{
	sem_unlink("/sem_forks");
	sem_unlink("/sem_print");
	sem_unlink("/sem_eat");
}

// NOTE argv 에러처리, argv 값을 t_info에 넣어줌
int	set_info_argv(t_info *info, int argc, char *argv[])
{
	if (argc != 5 && argc != 6)
		return (END);
	info->number_of_philosophers = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->meal_full = ft_atoi(argv[5]);
	return (CONTINUE);
}