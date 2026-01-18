/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2_lib.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 19:08:42 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/18 23:06:51 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	get_time_now(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == FAILUER)
		return (FAILUER);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

bool is_dead(t_info *info)
{
	int	flag;
	pthread_mutex_lock(&info->dead_lock);
	if (info->dead_flag == 1)
		flag = true;
	else
		flag = false;
	pthread_mutex_unlock(&info->dead_lock);
	return (flag);
}

