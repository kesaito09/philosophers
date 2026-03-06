/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_ops_meal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 13:02:50 by kesaitou          #+#    #+#             */
/*   Updated: 2026/03/06 13:02:50 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_infra.h"

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
