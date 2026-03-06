/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_ops_sync.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 08:20:29 by kesaitou          #+#    #+#             */
/*   Updated: 2026/03/06 00:00:00 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_infra.h"

bool	is_simulation_finished(t_philo *philo)
{
	t_philo_handler	*handler;
	bool			flag;

	handler = (t_philo_handler *)philo;
	if (!handler || !handler->info)
		return (true);
	if (retry_sem_wait(handler->info->state_lock) == FAILURE)
		return (true);
	flag = handler->info->is_stop_sim;
	if (sem_post(handler->info->state_lock) != 0)
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

int	ops_update_meal(t_philo *self)
{
	t_philo_handler	*handler;

	if (!self)
		return (FAILURE);
	handler = (t_philo_handler *)self;
	if (retry_sem_wait((sem_t *)handler->last_eat_lock) == FAILURE)
		return (FAILURE);
	self->time_last_eat = get_time_now();
	self->eat_count++;
	sem_post((sem_t *)handler->last_eat_lock);
	return (SUCCESS);
}

bool	ops_is_sated(t_philo *self)
{
	t_philo_handler	*handler;
	bool			sated;

	if (!self)
		return (false);
	handler = (t_philo_handler *)self;
	if (retry_sem_wait((sem_t *)handler->last_eat_lock) == FAILURE)
		return (false);
	sated = (self->eat_count >= self->rule->num_must_eat);
	sem_post((sem_t *)handler->last_eat_lock);
	return (sated);
}
