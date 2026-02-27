/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 05:42:48 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/27 06:01:47 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_infra.h"
#include <sys/time.h>
#include <unistd.h>

long	get_time_now(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (FAILURE);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	philo_usleep(t_philo *philo, long duration_ms)
{
	long	start;

	if (!philo || duration_ms <= 0)
		return ;
	start = get_time_now();
	while (!is_simulation_finished(philo))
	{
		if (get_time_now() - start >= duration_ms)
			break ;
		usleep(500);
	}
}
