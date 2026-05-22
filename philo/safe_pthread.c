/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_pthread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 00:00:00 by kesaitou          #+#    #+#             */
/*   Updated: 2026/05/22 00:00:00 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

int	safe_lock(pthread_mutex_t *mutex)
{
	if (pthread_mutex_lock(mutex) != PTHREAD_OK)
	{
		write(2, "Error: pthread_mutex_lock\n", 26);
		return (FAILURE);
	}
	return (SUCCESS);
}

void	safe_unlock(pthread_mutex_t *mutex)
{
	if (pthread_mutex_unlock(mutex) != PTHREAD_OK)
		write(2, "Error: pthread_mutex_unlock\n", 28);
}

void	safe_mutex_destroy(pthread_mutex_t *mutex)
{
	if (pthread_mutex_destroy(mutex) != PTHREAD_OK)
		write(2, "Error: pthread_mutex_destroy\n", 29);
}

void	safe_thread_join(pthread_t thread)
{
	if (pthread_join(thread, NULL) != PTHREAD_OK)
		write(2, "Error: pthread_join\n", 20);
}
