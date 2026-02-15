/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 19:08:42 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/15 16:15:00 by codex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_now(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (FAILURE);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	smart_sleep(t_philo *philo, long duration_ms)
{
	long	start;

	start = get_time_now();
	while (!is_simulation_finished(philo))
	{
		if (get_time_now() - start >= duration_ms)
			break ;
		usleep(500);
	}
	return (SUCCESS);
}
