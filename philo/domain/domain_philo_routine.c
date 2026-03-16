/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   domain_philo_routine.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:45:04 by kesaitou          #+#    #+#             */
/*   Updated: 2026/03/16 00:05:53 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_domain.h"

int			philo_eat(t_philo *philo);
int			domain_philo_think(t_philo *philo);
long		domain_get_odd_start_delay(t_philo *philo);

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
	long	delay_ms;

	delay_ms = 0;
	if (philo->rule->num_of_philo % 2 == 1)
		delay_ms = domain_get_odd_start_delay(philo);
	else if (philo->id % 2 == 0)
		delay_ms = philo->rule->time_to_eat / 2;
	return (philo->ops->sleep_ms(philo, delay_ms));
}

static int	philo_sleep(t_philo *philo)
{
	if (philo->ops->log_action(philo, STATE_SLEEP) == FAILURE)
		return (FAILURE);
	if (philo->ops->sleep_ms(philo, philo->rule->time_to_sleep) == FAILURE)
		return (FAILURE);
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
		if (domain_philo_think(philo) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}
