/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_ops_sync.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 17:17:03 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/25 17:17:11 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_infra.h"

void	ops_lock_acquire(void *lock)
{
	sync_take(lock);
}

void	ops_lock_release(void *lock)
{
	sync_release(lock);
}

int	ops_should_stop(t_philo *self)
{
	return (is_simulation_finished(self));
}
