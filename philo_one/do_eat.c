/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_eat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 21:00:55 by yunslee           #+#    #+#             */
/*   Updated: 2021/03/08 21:04:26 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// NOTE 철학자가 죽지 않도록하는 나의 알고리즘임
int	eat_one_direction(t_philo *philo, t_info *info)
{
}

// NOTE 먹는 행위.
int	eat(t_philo *philo, t_info *info)
{
	// 1. 누군가 죽었는지 판단해서 죽었다면, 바로 return 
	// 2. 먹는 알고리즘 info->forks에 대해서 mutex가 쓰임. 매우매우 중요한 부분

	// 나는 철학자가 죽지 않게 하는 알고리즘으로써 아래 함수를 썼음. 본인 방법을 생각해보면 좋을 듯
	// eat_one_direction(t_philo *philo, t_info *info)
}
