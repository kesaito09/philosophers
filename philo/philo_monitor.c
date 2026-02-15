/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 05:27:16 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/15 16:15:00 by codex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_simulation_stop(t_info *info)
{
	pthread_mutex_lock(&info->state_lock);
	info->is_stop_sim = true;
	pthread_mutex_unlock(&info->state_lock);
}

static bool	is_simulation_stopped(t_info *info)
{
	bool	stopped;

	pthread_mutex_lock(&info->state_lock);
	stopped = info->is_stop_sim;
	pthread_mutex_unlock(&info->state_lock);
	return (stopped);
}

static long	get_last_eat_time(t_philo *philo)
{
	long	last_time;

	pthread_mutex_lock(&philo->last_eat_lock);
	last_time = philo->time_last_eat;
	pthread_mutex_unlock(&philo->last_eat_lock);
	return (last_time);
}

static bool	is_philo_dead(t_philo *philo, t_info *info)
{
	if (get_time_now() - get_last_eat_time(philo) >= info->time_to_die)
		return (true);
	return (false);
}

static long	get_eat_count(t_philo *philo)
{
	long	eat_count;

	pthread_mutex_lock(&philo->last_eat_lock);
	eat_count = philo->eat_count;
	pthread_mutex_unlock(&philo->last_eat_lock);
	return (eat_count);
}

static bool	all_philosophers_sated(t_philo *philos, t_info *info)
{
	int	i;

	if (info->num_must_eat == UNSET_MUST_EAT)
		return (false);
	i = 0;
	while (i < info->num_of_philo)
	{
		if (get_eat_count(&philos[i]) < info->num_must_eat)
			return (false);
		i++;
	}
	return (true);
}

static bool	try_set_stop_and_lock_write(t_info *info)
{
	pthread_mutex_lock(&info->state_lock);
	if (info->is_stop_sim)
	{
		pthread_mutex_unlock(&info->state_lock);
		return (false);
	}
	info->is_stop_sim = true;
	pthread_mutex_lock(&info->write_lock);
	pthread_mutex_unlock(&info->state_lock);
	return (true);
}

static void	announce_death(t_philo *philo)
{
	long	elapsed;

	if (!try_set_stop_and_lock_write(philo->info))
		return ;
	elapsed = get_time_now() - philo->info->start_time;
	printf("%ld %d died\n", elapsed, philo->id);
	pthread_mutex_unlock(&philo->info->write_lock);
}

static int	check_death_and_stop(t_philo *philos, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philo)
	{
		if (is_philo_dead(&philos[i], info))
		{
			announce_death(&philos[i]);
			return (SUCCESS);
		}
		i++;
	}
	return (FAILURE);
}

int	monitoring(t_philo *philos, t_info *info)
{
	while (!is_simulation_stopped(info))
	{
		if (all_philosophers_sated(philos, info))
		{
			set_simulation_stop(info);
			return (SUCCESS);
		}
		if (check_death_and_stop(philos, info) == SUCCESS)
			return (SUCCESS);
		usleep(500);
	}
	return (SUCCESS);
}
