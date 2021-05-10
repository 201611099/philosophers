/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 21:15:14 by yunslee           #+#    #+#             */
/*   Updated: 2021/03/09 01:08:01 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

// NOTE argv 에러처리, argv 값을 t_info에 넣어줌
int		set_info_argv(t_info *info, int argc, char *argv[])
{
}

// NOTE (info->forks)포크에 대해서 하나씩 mutex_init 해주고, (info->print_mutex)print에 대해서도 mutex_init 해준다.
void	mutex_init(t_info *info)
{
}

// NOTE forks, basetime, anyone_dead, full_list을 초기화 해줌.
int		set_info(t_info *info)
{
}

// NOTE 철학자에 대한 정보 초기화 t_philo에 있는 값들 설정하기 
int		set_philos(t_philo *philos)
{
	unsigned long	init_time;
	int				i;

	i = 0;
	while (i < g_philo_num)
	{
		// t_philo[i]의 멤버 값들 설정하기
		i++;
	}
	return (1);
}
