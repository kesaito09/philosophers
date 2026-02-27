/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 17:38:49 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/25 17:53:47 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_infra.h"

int				ops_log_action(t_philo *self, t_state state);
long			ops_get_time(void);
int				ops_sleep_ms(t_philo *self, long duration_ms);
int				ops_take_forks(t_philo *self, void **first, void **second);
void			ops_drop_forks(t_philo *self, void *first, void *second);
void			ops_lock_acquire(void *lock);
void			ops_lock_release(void *lock);
int				ops_should_stop(t_philo *self);

t_domain_ops	*get_domain_ops(void)
{
	static t_domain_ops	domain_ops = {
		.log_action = ops_log_action,
		.get_time = ops_get_time,
		.sleep_ms = ops_sleep_ms,
		.take_forks = ops_take_forks,
		.drop_forks = ops_drop_forks,
		.lock_acquire = ops_lock_acquire,
		.lock_release = ops_lock_release,
		.should_stop = ops_should_stop,
	};

	return (&domain_ops);
}
