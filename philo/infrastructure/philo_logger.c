/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_logger.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:54:24 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/25 17:38:42 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_infra.h"
#include "philo_types.h"
#include "philo_domain.h"
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
	sync_take(philo->info->state_lock);
	if (philo->info->is_stop_sim && state != STATE_DIE)
	{
		sync_release(philo->info->state_lock);
		return (FAILURE);
	}
	sync_take(philo->info->write_lock);
	sync_release(philo->info->state_lock);
	print_state_log(philo, state);
	sync_release(philo->info->write_lock);
	return (SUCCESS);
}
