/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_ops_sync.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 08:20:29 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/27 08:20:51 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_infra.h"

bool	is_simulation_finished(t_philo *philo)
{
	bool	flag;

	if (!philo || !philo->info)
		return (true);
	if (retry_sem_wait(philo->info->state_lock) == FAILURE)
		return (true);
	flag = philo->info->is_stop_sim;
	if (sem_post(philo->info->state_lock) != 0)
		return (true);
	return (flag);
}

void	set_simulation_stop(t_info *info)
{
	if (retry_sem_wait(info->state_lock) == FAILURE)
		return ;
	info->is_stop_sim = true;
	sem_post(info->state_lock);
}

void	ops_lock_acquire(void *lock)
{
	if (!lock)
		return ;
	retry_sem_wait((sem_t *)lock);
}

void	ops_lock_release(void *lock)
{
	if (!lock)
		return ;
	sem_post((sem_t *)lock);
}

bool	ops_should_stop(t_philo *self)
{
	return (is_simulation_finished(self));
}
