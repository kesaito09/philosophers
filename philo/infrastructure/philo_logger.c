/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_logger.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:54:24 by kesaitou          #+#    #+#             */
/*   Updated: 2026/03/02 00:00:00 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_infra.h"
#include <stdio.h>

static const char	*get_message(t_state state)
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

int	logger(t_philo *philo, t_state state)
{
	t_philo_handler	*handler;
	long			elapsed;
	const char		*msg;

	handler = (t_philo_handler *)philo;
	if (!handler || !handler->info)
		return (FAILURE);
	sync_take(handler->info->write_lock);
	sync_take(handler->info->state_lock);
	if (handler->info->is_stop_sim && state != STATE_DIE)
	{
		sync_release(handler->info->state_lock);
		sync_release(handler->info->write_lock);
		return (FAILURE);
	}
	elapsed = get_time_now() - handler->info->start_time;
	msg = get_message(state);
	printf("%ld %d %s\n", elapsed, philo->id, msg);
	sync_release(handler->info->state_lock);
	sync_release(handler->info->write_lock);
	return (SUCCESS);
}
