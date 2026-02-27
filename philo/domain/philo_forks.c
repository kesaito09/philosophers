/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_forks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:55:29 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/25 16:57:21 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_domain.h"
#include "../include/philo_types.h"

static void	*first_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
		return (philo->right_fork);
	return (philo->left_fork);
}

static void	*second_fork(t_philo *philo)
{
	if (philo->id % 2 == 1)
		return (philo->left_fork);
	return (philo->right_fork);
}

int	philo_take_forks(t_philo *philo, void **first, void **second)
{
	if (!philo || !first || !second)
		return (FAILURE);
	*first = first_fork(philo);
	*second = second_fork(philo);
	philo->ops->lock_acquire(*first);
	philo->ops->lock_acquire(*second);
	return (SUCCESS);
}

void	philo_release_forks(t_philo *philo, void *first, void *second)
{
	if (second)
		philo->ops->lock_release(second);
	if (first)
		philo->ops->lock_release(first);
}
