/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_ops_forks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 05:50:04 by kesaitou          #+#    #+#             */
/*   Updated: 2026/03/06 00:00:00 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_infra.h"

int	ops_take_forks(t_philo *self)
{
	t_philo_handler	*handler;

	if (!self)
		return (FAILURE);
	handler = (t_philo_handler *)self;
	if (retry_sem_wait(handler->info->sem_sit) == FAILURE)
		return (FAILURE);
	if (retry_sem_wait(handler->info->forks) == FAILURE)
		return (sem_post(handler->info->sem_sit), FAILURE);
	if (retry_sem_wait(handler->info->forks) == FAILURE)
		return (sem_post(handler->info->forks),
			sem_post(handler->info->sem_sit), FAILURE);
	return (SUCCESS);
}

void	ops_drop_forks(t_philo *self)
{
	t_philo_handler	*handler;

	handler = (t_philo_handler *)self;
	sem_post(handler->info->forks);
	sem_post(handler->info->forks);
	sem_post(handler->info->sem_sit);
}
