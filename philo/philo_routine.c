/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 17:08:27 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/15 16:15:00 by codex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_simulation_finished(t_philo *philo)
{
	bool	flag;

	sync_take(&philo->info->state_lock);
	flag = philo->info->is_stop_sim;
	sync_release(&philo->info->state_lock);
	return (flag);
}

static int	handle_single_philo(t_philo *philo)
{
	sync_take(philo->left_fork);
	logger(philo, TAKE);
	while (!is_simulation_finished(philo))
		philo_usleep(philo, 1);
	sync_release(philo->left_fork);
	return (FAILURE);
}

static void	update_last_eat_time(t_philo *philo)
{
	sync_take(&philo->last_eat_lock);
	philo->time_last_eat = get_time_now();
	sync_release(&philo->last_eat_lock);
}

static void	increment_eat_count(t_philo *philo)
{
	sync_take(&philo->last_eat_lock);
	philo->eat_count++;
	sync_release(&philo->last_eat_lock);
}

static int	philo_eat(t_philo *philo)
{
	t_lock	*first;
	t_lock	*second;

	if (philo->info->num_of_philo == 1)
		return (handle_single_philo(philo));
	if (philo_take_forks(philo, &first, &second) == FAILURE)
		return (FAILURE);
	if (is_simulation_finished(philo))
		return (philo_release_forks(first, second), FAILURE);
	update_last_eat_time(philo);
	if (logger(philo, EAT) == FAILURE)
		return (philo_release_forks(first, second), FAILURE);
	philo_usleep(philo, philo->info->time_to_eat);
	increment_eat_count(philo);
	philo_release_forks(first, second);
	if (is_simulation_finished(philo))
		return (FAILURE);
	return (SUCCESS);
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
	unsigned long	think_time;

	if (logger(philo, THINK) == FAILURE)
		return (FAILURE);
	if (philo->info->num_of_philo % 2 == 0)
		return (SUCCESS);
	think_time = (philo->info->time_to_eat * 2) -
	philo->info->time_to_sleep;
	philo_usleep(philo, think_time);
	return (SUCCESS);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->info->num_of_philo % 2 == 0)
		philo_usleep(philo, 1);
	while (!is_simulation_finished(philo))
	{
		if (philo_eat(philo) == FAILURE)
			break ;
		if (philo_sleep(philo) == FAILURE)
			break ;
		if (philo_think(philo) == FAILURE)
			break ;
	}
	return (NULL);
}
