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

	pthread_mutex_lock(&philo->info->state_lock);
	flag = philo->info->is_stop_sim;
	pthread_mutex_unlock(&philo->info->state_lock);
	return (flag);
}

static pthread_mutex_t	*first_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
		return (philo->right_fork);
	return (philo->left_fork);
}

static pthread_mutex_t	*second_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
		return (philo->left_fork);
	return (philo->right_fork);
}

static int	handle_single_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	logger(philo, TAKE);
	while (!is_simulation_finished(philo))
		usleep(500);
	pthread_mutex_unlock(philo->left_fork);
	return (FAILURE);
}

static int	lock_and_log_fork(t_philo *philo, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
	if (logger(philo, TAKE) == FAILURE)
	{
		pthread_mutex_unlock(fork);
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	lock_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (philo->info->num_of_philo == 1)
		return (handle_single_philo(philo));
	first = first_fork(philo);
	second = second_fork(philo);
	if (lock_and_log_fork(philo, first) == FAILURE)
		return (FAILURE);
	if (lock_and_log_fork(philo, second) == FAILURE)
	{
		pthread_mutex_unlock(first);
		return (FAILURE);
	}
	return (SUCCESS);
}

static void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	update_last_eat_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_eat_lock);
	philo->time_last_eat = get_time_now();
	pthread_mutex_unlock(&philo->last_eat_lock);
}

static void	increment_eat_count(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_eat_lock);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->last_eat_lock);
}

static int	philo_eat(t_philo *philo)
{
	if (lock_forks(philo) == FAILURE)
		return (FAILURE);
	update_last_eat_time(philo);
	if (logger(philo, EAT) == FAILURE)
	{
		unlock_forks(philo);
		return (FAILURE);
	}
	smart_sleep(philo, philo->info->time_to_eat);
	increment_eat_count(philo);
	unlock_forks(philo);
	return (SUCCESS);
}

static int	philo_sleep_and_think(t_philo *philo)
{
	if (logger(philo, SLEEP) == FAILURE)
		return (FAILURE);
	smart_sleep(philo, philo->info->time_to_sleep);
	if (logger(philo, THINK) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!is_simulation_finished(philo))
	{
		if (philo_eat(philo) == FAILURE)
			break ;
		if (philo_sleep_and_think(philo) == FAILURE)
			break ;
	}
	return (NULL);
}
