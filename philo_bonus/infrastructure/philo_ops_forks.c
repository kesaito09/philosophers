/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_ops_forks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 05:50:04 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/27 05:52:05 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_infra.h"

int	ops_take_forks(t_philo *self)
{
	if (!self)
		return (FAILURE);
	if (retry_sem_wait(self->info->sem_sit) == FAILURE)
		return (FAILURE);
	if (retry_sem_wait(self->info->forks) == FAILURE)
		return (sem_post(self->info->sem_sit), FAILURE);
	if (retry_sem_wait(self->info->forks) == FAILURE)
		return (sem_post(self->info->forks), sem_post(self->info->sem_sit),
			FAILURE);
	return (SUCCESS);
}

void	ops_drop_forks(t_philo *self)
{
	sem_post(self->info->forks);
	sem_post(self->info->forks);
	sem_post(self->info->sem_sit);
}
