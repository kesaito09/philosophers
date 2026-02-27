/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_ops_core.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 17:13:03 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/25 17:13:15 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_infra.h"

int	ops_log_action(t_philo *self, t_state state)
{
	return (logger(self, state));
}

long	ops_get_time(void)
{
	return (get_time_now());
}

int	ops_sleep_ms(t_philo *self, long duration_ms)
{
	return (philo_usleep(self, duration_ms));
}
