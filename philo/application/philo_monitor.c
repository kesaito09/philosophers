/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:42:39 by kesaitou          #+#    #+#             */
/*   Updated: 2026/03/02 17:54:07 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_app.h"
#include "../include/philo_infra.h"

static int	is_simulation_stopped(t_info *info)
{
	int	stopped;

	sync_take(info->state_lock);
	stopped = info->is_stop_sim;
	sync_release(info->state_lock);
	return (stopped);
}

static int	all_philosophers_sated(t_philo_handler *philos, t_info *info)
{
	int		i;
	long	eat_count;

	if (info->rule.num_must_eat == UNSET_MUST_EAT)
		return (FAILURE);
	i = 0;
	while (i < info->rule.num_of_philo)
	{
		sync_take(philos[i].last_eat_lock);
		eat_count = philos[i].philo.eat_count;
		sync_release(philos[i].last_eat_lock);
		if (eat_count < info->rule.num_must_eat)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

static int	check_death_and_stop(t_philo_handler *philos, t_info *info)
{
	int		i;
	long	now;
	long	last_eat;

	i = 0;
	while (i < info->rule.num_of_philo)
	{
		now = get_time_now();
		sync_take(philos[i].last_eat_lock);
		last_eat = philos[i].philo.time_last_eat;
		sync_release(philos[i].last_eat_lock);
		if (now - last_eat > info->rule.time_to_die)
		{
			set_simulation_stop(info);
			logger(&philos[i].philo, STATE_DIE);
			return (SUCCESS);
		}
		i++;
	}
	return (FAILURE);
}

int	monitoring(t_philo_handler *philos)
{
	t_info	*info;

	if (!philos || !philos[0].info)
		return (FAILURE);
	info = philos[0].info;
	while (!is_simulation_stopped(info))
	{
		if (all_philosophers_sated(philos, info) == SUCCESS)
			return (set_simulation_stop(info), SUCCESS);
		if (check_death_and_stop(philos, info) == SUCCESS)
			return (SUCCESS);
		philo_usleep(&philos[0].philo, 1);
	}
	return (SUCCESS);
}
