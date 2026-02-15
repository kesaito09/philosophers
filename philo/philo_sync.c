/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sync.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:52:00 by codex             #+#    #+#             */
/*   Updated: 2026/02/15 21:52:00 by codex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sync_init(t_lock *lock)
{
	if (!lock)
		return (FAILURE);
	if (pthread_mutex_init(lock, NULL) != 0)
		return (FAILURE);
	return (SUCCESS);
}

void	sync_destroy(t_lock *lock)
{
	if (!lock)
		return ;
	pthread_mutex_destroy(lock);
}

void	sync_take(t_lock *lock)
{
	if (!lock)
		return ;
	pthread_mutex_lock(lock);
}

void	sync_release(t_lock *lock)
{
	if (!lock)
		return ;
	pthread_mutex_unlock(lock);
}
