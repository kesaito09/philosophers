/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_ops_forks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 17:15:56 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/25 17:17:00 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_infra.h"

static void	*first_fork(t_philo *philo)
{
	if (philo->id % 2 == 1)
		return (philo->right_fork);
	return (philo->left_fork);
}

static void	*second_fork(t_philo *philo)
{
	if (philo->id % 2 == 1)
		return (philo->left_fork);
	return (philo->right_fork);
}

int	ops_take_forks(t_philo *self, void **first, void **second)
{
	if (!self || !first || !second)
		return (FAILURE);
	*first = first_fork(self);
	*second = second_fork(self);
	sync_take(*first);
	sync_take(*second);
	return (SUCCESS);
}

void	ops_drop_forks(t_philo *self, void *first, void *second)
{
	(void)self;
	if (second)
		sync_release(second);
	if (first)
		sync_release(first);
}
