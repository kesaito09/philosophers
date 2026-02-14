/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 17:08:27 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/15 05:34:15 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	logger(philo, TAKE);
}

void	back_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*philo_eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->last_eat_lock);
	philo->time_last_eat = get_time_now();
	pthread_mutex_unlock(&philo->time_last_eat);
	logger(philo, EAT);
	usleep(philo->info.time_to_eat * 1000);
	back_table_forks(philo);
	philo->eat_count++;
}

void	*philo_sleep(t_philo *philo)
{
	logger(philo, SLEEP);
	usleep(philo->info.time_to_sleep * 1000);
}

void	*philo_think(t_philo *philo)
{
	logger(philo, THINK);
}

void	*philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 1)
		usleep(philo->info.time_to_eat / 2);
	while (!is_simulation_finished(philo))
	{
		take_forks(philo);
		philo_eat(philo);
		back_forks(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
