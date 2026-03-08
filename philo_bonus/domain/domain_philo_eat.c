/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   domain_philo_eat.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:45:09 by kesaitou          #+#    #+#             */
/*   Updated: 2026/03/06 00:00:00 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_domain.h"

static int	wait_single_philo(t_philo *philo)
{
	if (philo->ops->take_forks(philo) == FAILURE)
		return (FAILURE);
	while (!philo->ops->should_stop(philo))
		philo->ops->sleep_ms(philo, 1);
	philo->ops->drop_forks(philo);
	return (SUCCESS);
}

static int	eat_with_forks(t_philo *philo)
{
	if (philo->ops->take_forks(philo) == FAILURE)
		return (FAILURE);
	if (philo->ops->update_meal(philo) == FAILURE
		|| philo->ops->log_action(philo, STATE_EAT) == FAILURE)
	{
		philo->ops->drop_forks(philo);
		return (FAILURE);
	}
	philo->ops->sleep_ms(philo, philo->rule->time_to_eat);
	philo->ops->drop_forks(philo);
	return (SUCCESS);
}

int	philo_eat(t_philo *philo)
{
	if (!philo || !philo->rule || !philo->ops)
		return (FAILURE);
	if (philo->rule->num_of_philo == 1)
		return (wait_single_philo(philo));
	return (eat_with_forks(philo));
}
