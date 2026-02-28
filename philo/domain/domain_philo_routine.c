/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   domain_philo_routine.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:45:04 by kesaitou          #+#    #+#             */
/*   Updated: 2026/03/01 02:51:15 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_types.h"

int	philo_eat(t_philo *philo);

int	is_philo_sated(t_philo *philo)
{
	int	sated;

	if (philo->info->num_must_eat == UNSET_MUST_EAT)
		return (FAILURE);
	philo->ops->lock_acquire(philo->last_eat_lock);
	sated = (philo->eat_count >= philo->info->num_must_eat);
	philo->ops->lock_release(philo->last_eat_lock);
	if (sated)
		return (SUCCESS);
	return (FAILURE);
}

static int	delay_start(t_philo *philo)
{
	if (philo->id % 2 == 0)
		return (philo->ops->sleep_ms(philo, philo->info->time_to_eat / 2));
	return (SUCCESS);
}

static int	philo_sleep(t_philo *philo)
{
	if (philo->ops->log_action(philo, STATE_SLEEP) == FAILURE)
		return (FAILURE);
	if (philo->ops->sleep_ms(philo, philo->info->time_to_sleep) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int	philo_think(t_philo *philo)
{
	long	think_time;
	int		group;

	group = philo->info->num_of_philo % 2 + 2;
	if (philo->ops->log_action(philo, STATE_THINK) == FAILURE)
		return (FAILURE);
	think_time = (philo->info->time_to_eat * (group - 1) - philo->info->time_to_sleep);
	if (think_time < 0)
		think_time = 0;
	think_time += (philo->info->time_to_die - (philo->info->time_to_eat * group)) / 3;
	philo->ops->sleep_ms(philo, think_time);
	return (SUCCESS);
}

int	domain_philo_routine(t_philo *philo)
{
	if (!philo || !philo->info || !philo->ops)
		return (FAILURE);
	if (delay_start(philo) == FAILURE)
		return (FAILURE);
	while (!philo->ops->should_stop(philo))
	{
		if (philo_eat(philo) == FAILURE)
			return (FAILURE);
		if (is_philo_sated(philo) == SUCCESS)
			break ;
		if (philo_sleep(philo) == FAILURE)
			return (FAILURE);
		if (philo_think(philo) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}
