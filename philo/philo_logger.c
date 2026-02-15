/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_logger.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 22:56:37 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/15 16:15:00 by codex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static const char	*get_message(t_state state)
{
	if (state == TAKE)
		return ("has taken a fork");
	if (state == EAT)
		return ("is eating");
	if (state == SLEEP)
		return ("is sleeping");
	if (state == THINK)
		return ("is thinking");
	if (state == DIE)
		return ("died");
	return ("error");
}

static int	can_print_state(t_philo *philo, t_state state)
{
	pthread_mutex_lock(&philo->info->state_lock);
	if (philo->info->is_stop_sim && state != DIE)
	{
		pthread_mutex_unlock(&philo->info->state_lock);
		return (FAILURE);
	}
	return (SUCCESS);
}

static void	unlock_state_after_print_check(t_philo *philo)
{
	pthread_mutex_unlock(&philo->info->state_lock);
}

static void	print_state_log(t_philo *philo, t_state state)
{
	long			elapsed;
	const char		*msg;

	elapsed = get_time_now() - philo->info->start_time;
	msg = get_message(state);
	printf("%ld %d %s\n", elapsed, philo->id, msg);
}

int	logger(t_philo *philo, t_state state)
{
	if (can_print_state(philo, state) == FAILURE)
		return (FAILURE);
	pthread_mutex_lock(&philo->info->write_lock);
	unlock_state_after_print_check(philo);
	print_state_log(philo, state);
	pthread_mutex_unlock(&philo->info->write_lock);
	return (SUCCESS);
}
