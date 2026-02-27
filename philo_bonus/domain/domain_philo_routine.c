/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   domain_philo_routine.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 08:30:59 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/27 08:32:09 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_domain.h"
#include "../include/philo_types.h"

int	domain_is_sated(t_philo *philo)
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

static int	sleep_state(t_philo *philo)
{
	if (philo->ops->log_action(philo, STATE_SLEEP) == FAILURE)
		return (FAILURE);
	philo->ops->sleep_ms(philo, philo->info->time_to_sleep);
	return (SUCCESS);
}

static int	think_state(t_philo *philo)
{
	long	think_time;
	int		group;

	group = philo->info->num_of_philo % 2 + 2;
	if (philo->ops->log_action(philo, STATE_THINK) == FAILURE)
		return (FAILURE);
	think_time = (philo->info->time_to_eat * (group - 1)
			- philo->info->time_to_sleep);
	if (think_time < 0)
		think_time = 0;
	think_time += (philo->info->time_to_die - (philo->info->time_to_eat
				* group)) / 2;
	philo->ops->sleep_ms(philo, think_time);
	return (SUCCESS);
}

int	domain_philo_routine(t_philo *philo)
{
	if (!philo || !philo->info || !philo->ops)
		return (FAILURE);
	if (philo->id % 2 == 0)
		philo->ops->sleep_ms(philo, philo->info->time_to_eat / 2);
	while (!philo->ops->should_stop(philo))
	{
		if (domain_philo_eat(philo) == FAILURE)
			return (FAILURE);
		if (domain_is_sated(philo) == SUCCESS)
			break ;
		if (sleep_state(philo) == FAILURE)
			return (FAILURE);
		if (think_state(philo) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}
