/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_ops_core.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 08:21:03 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/27 08:21:08 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_infra.h"
#include <errno.h>

int	retry_sem_wait(sem_t *sem)
{
	while (sem_wait(sem) == -1)
	{
		if (errno != EINTR)
			return (FAILURE);
	}
	return (SUCCESS);
}

int	ops_log_action(t_philo *self, t_state state)
{
	return (logger(self, state));
}

long	ops_get_time(void)
{
	return (get_time_now());
}

void	ops_sleep_ms(t_philo *self, long duration_ms)
{
	philo_usleep(self, duration_ms);
}
