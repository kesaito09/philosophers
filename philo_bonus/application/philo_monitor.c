/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 05:30:28 by kesaitou          #+#    #+#             */
/*   Updated: 2026/03/06 00:00:00 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_app.h"
#include "../include/philo_infra.h"
#include <stdlib.h>
#include <unistd.h>

static long	get_last_eat_time(t_philo_handler *handler)
{
	long	last_eat;

	if (!handler)
		return (FAILURE);
	if (retry_sem_wait((sem_t *)handler->last_eat_lock) == FAILURE)
		return (FAILURE);
	last_eat = handler->philo.time_last_eat;
	if (sem_post((sem_t *)handler->last_eat_lock) != 0)
		return (FAILURE);
	return (last_eat);
}

static void	handle_death(t_philo_handler *handler)
{
	set_simulation_stop(handler->info);
	logger(&handler->philo, STATE_DIE);
	exit(EXIT_DEAD);
}

static void	*monitor_routine(void *arg)
{
	t_philo_handler	*handler;
	long			last_eat;

	handler = (t_philo_handler *)arg;
	while (!is_simulation_finished(&handler->philo))
	{
		last_eat = get_last_eat_time(handler);
		if (last_eat == FAILURE)
		{
			set_simulation_stop(handler->info);
			exit(EXIT_ERROR);
		}
		if (get_time_now() - last_eat > handler->info->rule.time_to_die)
			handle_death(handler);
		usleep(500);
	}
	return (NULL);
}

int	start_monitor_thread(t_philo_handler *handler)
{
	pthread_t	monitor;

	if (pthread_create(&monitor, NULL, monitor_routine, handler) != 0)
		return (FAILURE);
	if (pthread_detach(monitor) != 0)
		return (FAILURE);
	return (SUCCESS);
}

int	run_philo_process(t_philo_handler *handler)
{
	int	result;

	if (start_monitor_thread(handler) == FAILURE)
		return (FAILURE);
	result = domain_philo_routine(&handler->philo);
	set_simulation_stop(handler->info);
	return (result);
}
