/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 17:38:49 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/28 15:06:19 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_infra.h"

int				logger(t_philo *philo, t_state state);
void			sync_take(void *lock);
void			sync_release(void *lock);
int				ops_take_forks(t_philo *self, void **first, void **second);
void			ops_drop_forks(t_philo *self, void *first, void *second);
long			get_time_now(void);
int				philo_usleep(t_philo *philo, long duration_ms);
bool			is_simulation_finished(t_philo *philo);

t_domain_ops	*get_domain_ops(void)
{
	static t_domain_ops domain_ops = {
		.log_action = logger,
		.get_time = get_time_now,
		.sleep_ms = philo_usleep,
		.take_forks = ops_take_forks,
		.drop_forks = ops_drop_forks,
		.lock_acquire = sync_take,
		.lock_release = sync_release,
		.should_stop = is_simulation_finished,
	};
	return (&domain_ops);
}
