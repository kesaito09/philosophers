/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:45:09 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/27 06:10:42 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_types.h"

static int	wait_childrensingle_philo(t_philo *philo)
{
	philo->ops->lock_acquire(philo->left_fork);
	if (philo->ops->log_action(philo, STATE_TAKE_FORK) == FAILURE)
	{
		philo->ops->lock_release(philo->left_fork);
		return (FAILURE);
	}
	while (!philo->ops->should_stop(philo))
		philo->ops->sleep_ms(philo, 1);
	philo->ops->lock_release(philo->left_fork);
	return (SUCCESS);
}

static int	update_meal_state(t_philo *philo)
{
	philo->ops->lock_acquire(philo->last_eat_lock);
	philo->time_last_eat = philo->ops->get_time();
	philo->eat_count++;
	philo->ops->lock_release(philo->last_eat_lock);
	return (SUCCESS);
}

static void	release_forks(t_philo *philo, void *first, void *second)
{
	philo->ops->drop_forks(philo, first, second);
}

static int	eat_with_forks(t_philo *philo)
{
	void	*first;
	void	*second;

	if (philo->ops->take_forks(philo, &first, &second) == FAILURE)
		return (FAILURE);
	if (philo->ops->log_action(philo, STATE_TAKE_FORK) == FAILURE
		|| philo->ops->log_action(philo, STATE_TAKE_FORK) == FAILURE
		|| update_meal_state(philo) == FAILURE
		|| philo->ops->log_action(philo, STATE_EAT) == FAILURE)
	{
		release_forks(philo, first, second);
		return (FAILURE);
	}
	philo->ops->sleep_ms(philo, philo->info->time_to_eat);
	release_forks(philo, first, second);
	return (SUCCESS);
}

int	philo_eat(t_philo *philo)
{
	if (!philo || !philo->info || !philo->ops)
		return (FAILURE);
	if (philo->info->num_of_philo == 1)
		return (wait_childrensingle_philo(philo));
	return (eat_with_forks(philo));
}
