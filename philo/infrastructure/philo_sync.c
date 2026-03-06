/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sync.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 17:17:17 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/28 15:01:51 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_infra.h"
#include <pthread.h>
#include <stdlib.h>

void	*sync_create(void)
{
	pthread_mutex_t	*lock;

	lock = ft_calloc(1, sizeof(pthread_mutex_t));
	if (!lock)
		return (NULL);
	if (pthread_mutex_init(lock, NULL) != 0)
	{
		free(lock);
		return (NULL);
	}
	return (lock);
}

void	sync_destroy(void *lock)
{
	pthread_mutex_t	*mutex;

	if (!lock)
		return ;
	mutex = (pthread_mutex_t *)lock;
	pthread_mutex_destroy(mutex);
	free(mutex);
}

void	sync_take(void *lock)
{
	if (!lock)
		return ;
	pthread_mutex_lock((pthread_mutex_t *)lock);
}

void	sync_release(void *lock)
{
	if (!lock)
		return ;
	pthread_mutex_unlock((pthread_mutex_t *)lock);
}
