/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 12:00:00 by kesaitou          #+#    #+#             */
/*   Updated: 2026/05/17 14:00:00 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>

static const char	*state_message(t_state state);
static bool			check_dead(t_info *info);
static bool			check_all_sated(t_info *info);

int	monitor_loop(t_info *info)
{
	if (!info)
		return (FAILURE);
	while (!is_stopped(info))
	{
		if (check_dead(info))
			return (SUCCESS);
		if (check_all_sated(info))
			return (SUCCESS);
		usleep(200);
	}
	return (SUCCESS);
}

int	log_action(t_philo *philo, t_state state)
{
	t_sim_state	*s;
	long		elapsed;

	if (!philo || !philo->info)
		return (FAILURE);
	s = &philo->info->sim;
	pthread_mutex_lock(&s->write_lock);
	pthread_mutex_lock(&s->state_lock);
	if (s->is_stopped && state != STATE_DIE)
	{
		pthread_mutex_unlock(&s->state_lock);
		pthread_mutex_unlock(&s->write_lock);
		return (STOPPED);
	}
	elapsed = get_time_ms() - s->start_time;
	printf("%ld %d %s\n", elapsed, philo->id, state_message(state));
	pthread_mutex_unlock(&s->state_lock);
	pthread_mutex_unlock(&s->write_lock);
	return (SUCCESS);
}

static const char	*state_message(t_state state)
{
	if (state == STATE_TAKE_FORK)
		return ("has taken a fork");
	if (state == STATE_EAT)
		return ("is eating");
	if (state == STATE_SLEEP)
		return ("is sleeping");
	if (state == STATE_THINK)
		return ("is thinking");
	if (state == STATE_DIE)
		return ("died");
	return ("error");
}

static bool	check_dead(t_info *info)
{
	int		i;
	long	elapsed;

	i = 0;
	while (i < info->rule.num_of_philo)
	{
		pthread_mutex_lock(&info->philos[i].meal.lock);
		elapsed = get_time_ms() - info->philos[i].meal.last_time;
		pthread_mutex_unlock(&info->philos[i].meal.lock);
		if (elapsed >= info->rule.time_to_die)
		{
			stop_simulation(info);
			log_action(&info->philos[i], STATE_DIE);
			return (true);
		}
		i++;
	}
	return (false);
}

static bool	check_all_sated(t_info *info)
{
	int		i;
	long	count;

	if (info->rule.num_must_eat == UNSET_MUST_EAT)
		return (false);
	i = 0;
	while (i < info->rule.num_of_philo)
	{
		pthread_mutex_lock(&info->philos[i].meal.lock);
		count = info->philos[i].meal.count;
		pthread_mutex_unlock(&info->philos[i].meal.lock);
		if (count < info->rule.num_must_eat)
			return (false);
		i++;
	}
	stop_simulation(info);
	return (true);
}
