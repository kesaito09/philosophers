/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 12:00:00 by kesaitou          #+#    #+#             */
/*   Updated: 2026/05/17 14:00:00 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	take_fork_single(t_philo *philo);
static int	take_two_forks(t_philo *philo, pthread_mutex_t *first,
				pthread_mutex_t *second);

int	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (!philo)
		return (FAILURE);
	if (philo->info->rule.num_of_philo == 1)
		return (take_fork_single(philo));
	if (philo->id % 2 == 0)
	{
		first = philo->left_fork;
		second = philo->right_fork;
	}
	else
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	return (take_two_forks(philo, first, second));
}

void	drop_forks(t_philo *philo)
{
	if (!philo)
		return ;
	if (philo->info->rule.num_of_philo == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static int	take_fork_single(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (log_action(philo, STATE_TAKE_FORK) != SUCCESS)
	{
		pthread_mutex_unlock(philo->left_fork);
		return (STOPPED);
	}
	philo_usleep(philo, philo->info->rule.time_to_die);
	pthread_mutex_unlock(philo->left_fork);
	return (STOPPED);
}

static int	take_two_forks(t_philo *philo, pthread_mutex_t *first,
		pthread_mutex_t *second)
{
	pthread_mutex_lock(first);
	if (log_action(philo, STATE_TAKE_FORK) != SUCCESS)
	{
		pthread_mutex_unlock(first);
		return (STOPPED);
	}
	pthread_mutex_lock(second);
	if (log_action(philo, STATE_TAKE_FORK) != SUCCESS)
	{
		pthread_mutex_unlock(second);
		pthread_mutex_unlock(first);
		return (STOPPED);
	}
	return (SUCCESS);
}
