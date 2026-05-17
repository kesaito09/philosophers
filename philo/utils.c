/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 12:00:00 by kesaitou          #+#    #+#             */
/*   Updated: 2026/05/17 14:00:00 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

long	get_time_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (0);
	return ((long)tv.tv_sec * 1000 + (long)tv.tv_usec / 1000);
}

int	philo_usleep(t_philo *philo, long duration_ms)
{
	long	start;
	long	remaining;

	if (!philo || duration_ms <= 0)
		return (SUCCESS);
	start = get_time_ms();
	while (1)
	{
		if (is_stopped(philo->info))
			return (STOPPED);
		remaining = duration_ms - (get_time_ms() - start);
		if (remaining <= 0)
			break ;
		if (remaining > 10)
			usleep(1000);
		else if (remaining > 1)
			usleep(100);
	}
	return (SUCCESS);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*arr;
	size_t	total;

	if (size != 0 && nmemb > ((size_t) - 1) / size)
		return (NULL);
	total = nmemb * size;
	arr = malloc(total);
	if (!arr)
		return (NULL);
	memset(arr, 0, total);
	return (arr);
}

bool	is_stopped(t_info *info)
{
	bool	flag;

	if (!info)
		return (true);
	pthread_mutex_lock(&info->sim.state_lock);
	flag = info->sim.is_stopped;
	pthread_mutex_unlock(&info->sim.state_lock);
	return (flag);
}

void	stop_simulation(t_info *info)
{
	if (!info)
		return ;
	pthread_mutex_lock(&info->sim.state_lock);
	info->sim.is_stopped = true;
	pthread_mutex_unlock(&info->sim.state_lock);
}
