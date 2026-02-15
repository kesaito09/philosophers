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
	sync_take(&info->state_lock);
	info->is_stop_sim = true;
	sync_release(&info->state_lock);
}

static bool	is_simulation_stopped(t_info *info)
{
	bool	stopped;

	sync_take(&info->state_lock);
	stopped = info->is_stop_sim;
	sync_release(&info->state_lock);
	return (stopped);
}

static long	get_last_eat_time(t_philo *philo)
{
	long	last_time;

	sync_take(&philo->last_eat_lock);
	last_time = philo->time_last_eat;
	sync_release(&philo->last_eat_lock);
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

	sync_take(&philo->last_eat_lock);
	eat_count = philo->eat_count;
	sync_release(&philo->last_eat_lock);
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

static void	announce_death(t_philo *philo)
{
	t_info	*info;
	long	elapsed;

	info = philo->info;
	sync_take(&info->state_lock);
	if (info->is_stop_sim)
	{
		sync_release(&info->state_lock);
		return ;
	}
	info->is_stop_sim = true;
	sync_take(&info->write_lock);
	sync_release(&info->state_lock);
	elapsed = get_time_now() - info->start_time;
	printf("%ld %d died\n", elapsed, philo->id);
	sync_release(&info->write_lock);
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
		philo_usleep(&philos[0], 1);
	}
	return (SUCCESS);
}
