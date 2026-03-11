/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   domain_philo_routine.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:45:04 by kesaitou          #+#    #+#             */
/*   Updated: 2026/03/11 22:31:57 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_domain.h"

int			philo_eat(t_philo *philo);

int	is_philo_sated(t_philo *philo)
{
	if (philo->rule->num_must_eat == UNSET_MUST_EAT)
		return (FAILURE);
	if (philo->ops->is_sated(philo))
		return (SUCCESS);
	return (FAILURE);
}

static int	delay_start(t_philo *philo)
{
	if (philo->id % 2 == 0)
		return (philo->ops->sleep_ms(philo, philo->rule->time_to_eat / 2));
	return (SUCCESS);
}

static int	philo_sleep(t_philo *philo)
{
	if (philo->ops->log_action(philo, STATE_SLEEP) == FAILURE)
		return (FAILURE);
	if (philo->ops->sleep_ms(philo, philo->rule->time_to_sleep) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int	philo_think(t_philo *philo)
{
	long	required_wait;
	int		group;
	long	safety_buffer;

	group = philo->rule->num_of_philo % 2 + 2;
	if (philo->ops->log_action(philo, STATE_THINK) == FAILURE)
		return (FAILURE);
	required_wait = (philo->rule->time_to_eat * (group - 1)
			- philo->rule->time_to_sleep);
	if (required_wait < 0)
		required_wait = 0;
	safety_buffer = philo->rule->time_to_die
		- (philo->rule->time_to_eat * group);
	if (safety_buffer < 40)
		required_wait = 0;
	else
		required_wait += safety_buffer / 2;
	philo->ops->sleep_ms(philo, required_wait);
	return (SUCCESS);
}

int	domain_philo_routine(t_philo *philo)
{
	if (!philo || !philo->rule || !philo->ops)
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
