/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 05:30:28 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/27 08:30:08 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_app.h"
#include "../include/philo_domain.h"
#include "../include/philo_infra.h"
#include <stdlib.h>
#include <unistd.h>

static long	get_last_eat_time(t_philo *philo)
{
	long	last_eat;

	if (!philo)
		return (FAILURE);
	if (retry_sem_wait((sem_t *)philo->last_eat_lock) == FAILURE)
		return (FAILURE);
	last_eat = philo->time_last_eat;
	if (sem_post((sem_t *)philo->last_eat_lock) != 0)
		return (FAILURE);
	return (last_eat);
}

static void	*monitor_routine(void *arg)
{
	t_philo	*philo;
	long	last_eat;

	philo = (t_philo *)arg;
	while (!is_simulation_finished(philo))
	{
		last_eat = get_last_eat_time(philo);
		if (last_eat == FAILURE)
		{
			set_simulation_stop(philo->info);
			exit(EXIT_ERROR);
		}
		if (get_time_now() - last_eat > philo->info->time_to_die)
		{
			set_simulation_stop(philo->info);
			logger(philo, STATE_DIE);
			exit(EXIT_DEAD);
		}
		usleep(500);
	}
	return (NULL);
}

int	monitoring(t_philo *philo)
{
	pthread_t	monitor;
	int			result;

	if (pthread_create(&monitor, NULL, monitor_routine, philo) != 0)
		return (FAILURE);
	if (pthread_detach(monitor) != 0)
		return (FAILURE);
	result = domain_philo_routine(philo);
	set_simulation_stop(philo->info);
	return (result);
}
