/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 17:38:49 by kesaitou          #+#    #+#             */
/*   Updated: 2026/03/06 00:00:00 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_infra.h"

int				logger(t_philo *philo, t_state state);
int				ops_take_fork(t_philo *self);
void			ops_drop_forks(t_philo *self);
int				ops_update_meal(t_philo *self);
bool			ops_is_sated(t_philo *self);
int				philo_usleep(t_philo *philo, long duration_ms);
bool			is_simulation_finished(t_philo *philo);

t_domain_ops	*get_domain_ops(void)
{
	static t_domain_ops	domain_ops = {
		.log_action = logger,
		.sleep_ms = philo_usleep,
		.take_forks = ops_take_fork,
		.drop_forks = ops_drop_forks,
		.update_meal = ops_update_meal,
		.is_sated = ops_is_sated,
		.should_stop = is_simulation_finished,
	};

	return (&domain_ops);
}
