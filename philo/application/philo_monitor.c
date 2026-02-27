/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:42:39 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/25 16:49:56 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_app.h"
#include "../include/philo_infra.h"
#include "../include/philo_types.h"

void	set_simulation_stop(t_info *info)
{
	sync_take(info->state_lock);
	info->is_stop_sim = true;
	sync_release(info->state_lock);
}

static int	is_simulation_stopped(t_info *info)
{
	int	stopped;

	sync_take(info->state_lock);
	stopped = info->is_stop_sim;
	sync_release(info->state_lock);
	return (stopped);
}

static int	all_philosophers_sated(t_philo *philos, t_info *info)
{
	int		i;
	long	eat_count;

	if (info->num_must_eat == UNSET_MUST_EAT)
		return (FAILURE);
	i = 0;
	while (i < info->num_of_philo)
	{
		sync_take(philos[i].last_eat_lock);
		eat_count = philos[i].eat_count;
		sync_release(philos[i].last_eat_lock);
		if (eat_count < info->num_must_eat)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

static int	check_death_and_stop(t_philo *philos, t_info *info)
{
	int		i;
	long	now;
	long	last_eat;

	i = 0;
	while (i < info->num_of_philo)
	{
		now = get_time_now();
		sync_take(philos[i].last_eat_lock);
		last_eat = philos[i].time_last_eat;
		sync_release(philos[i].last_eat_lock);
		if (now - last_eat > info->time_to_die)
		{
			set_simulation_stop(info);
			logger(&philos[i], STATE_DIE);
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
		if (all_philosophers_sated(philos, info) == SUCCESS)
			return (set_simulation_stop(info), SUCCESS);
		if (check_death_and_stop(philos, info) == SUCCESS)
			return (SUCCESS);
		philo_usleep(&philos[0], 1);
	}
	return (SUCCESS);
}
