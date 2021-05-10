/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 21:18:01 by yunslee           #+#    #+#             */
/*   Updated: 2021/03/08 21:19:11 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_absolute_time(void)
{
	struct timeval	time;
	unsigned long	milisecond;

	gettimeofday(&time, NULL);
	milisecond = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (milisecond);
}

unsigned long	get_relative_time(void)
{
	struct timeval	time;
	unsigned long	milisecond;
	unsigned long	relative_milisecond;

	gettimeofday(&time, NULL);
	milisecond = time.tv_sec * 1000 + time.tv_usec / 1000;
	relative_milisecond = milisecond - g_info.basetime;
	return (relative_milisecond);
}

int				spend_time_of(t_status doing)
{
	unsigned long milisecond;

	if (doing == EATING)
		milisecond = g_info.time_to_eat;
	if (doing == SLEEPING)
		milisecond = g_info.time_to_sleep;
	accurate_sleep(milisecond);
	return (1);
}


// NOTE usleep() 대신에 이 함수를 쓰는 이유를 아래 슬랙을 통해서 숙지하길 바람.
// https://42born2code.slack.com/archives/CU6MU5TB7/p1608577708286600?thread_ts=1608559809.272100&cid=CU6MU5TB7
void			accurate_sleep(unsigned long milisecond)
{
	unsigned long	base;
	unsigned long	cur;

	base = get_absolute_time();
	while (1)
	{
		cur = get_absolute_time();
		if (milisecond < cur - base)
			return ;
		usleep(500);
	}
}
