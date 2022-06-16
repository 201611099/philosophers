/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 20:47:30 by hyojlee           #+#    #+#             */
/*   Updated: 2022/06/15 20:52:25 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isblank(char c)
{
	if (c == ' ' || c == '\n' || c == '\r'
		|| c == '\v' || c == '\f' || c == '\t')
		return (1);
	return (0);
}

static int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

t_info	*info(void)
{
	static t_info	info;

	return (&info);
}

int	ft_atoi(const char *str)
{
	char		*s;
	long long	ret;
	long long	flag;

	s = (char *)str;
	ret = 0;
	flag = 1;
	while (ft_isblank(*s) && *s)
		s++;
	if ((*s == '-') || (*s == '+'))
		if (*s++ == '-')
			flag *= -1;
	while (ft_isdigit(*s))
	{
		ret = ret * 10 + *s - '0';
		if (ret < 0)
		{
			if (flag < 0)
				return (0);
			else
				return (-1);
		}
		s++;
	}
	return (ret * flag);
}

void	free_all(t_philo *philos)
{
	free(philos);
	free(info()->forks);
	if (info()->meal_full)
		free(info()->full_list);
}