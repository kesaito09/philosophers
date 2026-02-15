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
	sync_take(&philo->info->state_lock);
	if (philo->info->is_stop_sim && state != DIE)
	{
		sync_release(&philo->info->state_lock);
		return (FAILURE);
	}
	sync_take(&philo->info->write_lock);
	sync_release(&philo->info->state_lock);
	print_state_log(philo, state);
	sync_release(&philo->info->write_lock);
	return (SUCCESS);
}
