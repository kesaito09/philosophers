/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 17:38:49 by kesaitou          #+#    #+#             */
/*   Updated: 2026/03/06 12:38:20 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_infra.h"

int				ops_take_forks(t_philo *self);
void			ops_drop_forks(t_philo *self);
int				ops_update_meal(t_philo *self);
bool			ops_is_sated(t_philo *self);

t_domain_ops	*get_domain_ops(void)
{
	static t_domain_ops	ops;

	ops.take_forks = ops_take_forks;
	ops.drop_forks = ops_drop_forks;
	ops.log_action = logger;
	ops.update_meal = ops_update_meal;
	ops.is_sated = ops_is_sated;
	ops.should_stop = is_simulation_finished;
	ops.last_meal_ms = ops_get_last_meal_ms;
	ops.now_ms = get_time_now;
	ops.sleep_ms = philo_usleep;
	return (&ops);
}
