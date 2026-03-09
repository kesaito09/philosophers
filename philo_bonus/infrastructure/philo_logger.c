/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_logger.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 03:05:41 by kesaitou          #+#    #+#             */
/*   Updated: 2026/03/06 00:00:00 by kesaitou         ###   ########.fr       */
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

static bool	is_log_allowed(t_philo_handler *handler, t_state state)
{
	if (handler->info->is_stop_sim && state != STATE_DIE)
		return (false);
	return (true);
}

static int	unlock_logger(sem_t *write_lock, sem_t *state_lock, int result)
{
	if (state_lock && sem_post(state_lock) != 0)
		result = FAILURE;
	if (sem_post(write_lock) != 0)
		return (FAILURE);
	return (result);
}

int	logger(t_philo *philo, t_state state)
{
	t_philo_handler	*handler;
	long			elapsed;
	const char		*msg;

	handler = (t_philo_handler *)philo;
	if (!handler || !handler->info)
		return (FAILURE);
	if (retry_sem_wait(handler->info->write_lock) == FAILURE)
		return (FAILURE);
	if (retry_sem_wait(handler->info->state_lock) == FAILURE)
		return (unlock_logger(handler->info->write_lock, NULL, FAILURE));
	if (!is_log_allowed(handler, state))
		return (unlock_logger(handler->info->write_lock,
				handler->info->state_lock, FAILURE));
	elapsed = get_time_now() - handler->info->start_time;
	msg = get_message(state);
	printf("%ld %d %s\n", elapsed, philo->id, msg);
	if (state == STATE_DIE)
		return (sem_post(handler->info->state_lock), SUCCESS);
	return (unlock_logger(handler->info->write_lock,
			handler->info->state_lock, SUCCESS));
}
