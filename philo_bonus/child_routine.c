/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 20:20:00 by codex             #+#    #+#             */
/*   Updated: 2026/02/22 20:20:00 by codex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "setup_contract.h"

static int	is_sated(t_philo *philo)
{
	long	eat_count;

	if (philo->info->num_must_eat == UNSET_MUST_EAT)
		return (FAILURE);
	while (sem_wait(philo->sem_meal) == -1)
	{
		if (errno != EINTR)
			return (FAILURE);
	}
	eat_count = philo->eat_count;
	if (sem_post(philo->sem_meal) != 0)
		return (FAILURE);
	if (eat_count >= philo->info->num_must_eat)
		return (SUCCESS);
	return (FAILURE);
}

static int	philo_sleep(t_philo *philo)
{
	if (logger(philo, SLEEP) == FAILURE)
		return (FAILURE);
	philo_usleep(philo, philo->info->time_to_sleep);
	return (SUCCESS);
}

static int	philo_think(t_philo *philo)
{
	int		group_size;
	long	think_time;

	if (logger(philo, THINK) == FAILURE)
		return (FAILURE);
	group_size = (philo->info->num_of_philo % 2) + 2;
	think_time = (philo->info->time_to_eat * (group_size - 1))
		- philo->info->time_to_sleep;
	if (think_time > 0)
		philo_usleep(philo, think_time);
	return (SUCCESS);
}

int	philo_routine(t_philo *philo)
{
	if (philo->info->num_of_philo % 2 == 0)
		philo_usleep(philo, 1);
	while (!is_simulation_finished(philo))
	{
		if (philo_eat(philo) == FAILURE)
			break ;
		if (is_sated(philo) == SUCCESS)
			return (SUCCESS);
		if (philo_sleep(philo) == FAILURE)
			break ;
		if (philo_think(philo) == FAILURE)
			break ;
	}
	return (FAILURE);
}
