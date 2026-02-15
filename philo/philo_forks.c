/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_forks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:55:00 by codex             #+#    #+#             */
/*   Updated: 2026/02/15 21:55:00 by codex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_lock	*first_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
		return (philo->right_fork);
	return (philo->left_fork);
}

static t_lock	*second_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
		return (philo->left_fork);
	return (philo->right_fork);
}

int	philo_take_forks(t_philo *philo, t_lock **first, t_lock **second)
{
	if (!philo || !first || !second)
		return (FAILURE);
	*first = first_fork(philo);
	*second = second_fork(philo);
	sync_take(*first);
	if (logger(philo, TAKE) == FAILURE)
		return (sync_release(*first), FAILURE);
	sync_take(*second);
	if (logger(philo, TAKE) == FAILURE)
		return (sync_release(*second), sync_release(*first), FAILURE);
	return (SUCCESS);
}

void	philo_release_forks(t_lock *first, t_lock *second)
{
	if (second)
		sync_release(second);
	if (first)
		sync_release(first);
}
