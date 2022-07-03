/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 20:47:30 by hyojlee           #+#    #+#             */
/*   Updated: 2022/07/02 22:24:06 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(char *arg, int *err)
{
	int			idx;
	long long	ret[2];

	idx = 0;
	ret[0] = 0;
	ret[1] = 1;
	while (arg[idx] == ' ')
		idx++;
	if (arg[idx] == '-')
		ret[1] = -1;
	if (arg[idx] == '-' || arg[idx] == '+')
		idx++;
	while (arg[idx])
	{
		if (!ft_isdigit(arg[idx]))
		{
			if (arg[idx++] == ' ')
				continue ;
			*err = ERROR;
		}
		ret[0] = ret[0] * 10 + arg[idx++] - '0';
	}
	if (ret[0] * ret[1] > INT_MAX || ret[0] * ret[1] < INT_MIN)
		*err = ERROR;
	return ((int)(ret[0] * ret[1]));
}

int	free_info(int ret)
{
	free(info()->forks);
	if (info()->num_of_meals)
		free(info()->full_list);
	return (ret);
}

int	free_all(t_philo *philos, int ret)
{
	mutex_destroy(info()->num_of_philos);
	free(philos);
	return (free_info(ret));
}
