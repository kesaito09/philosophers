/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_domain.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 04:56:03 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/27 06:01:47 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_DOMAIN_H
# define PHILO_DOMAIN_H

# include <stdbool.h>

typedef struct s_philo		t_philo;
typedef struct s_domain_ops	t_domain_ops;

typedef enum e_state
{
	STATE_TAKE_FORK,
	STATE_EAT,
	STATE_SLEEP,
	STATE_THINK,
	STATE_DIE,
}							t_state;

struct						s_domain_ops
{
	int						(*log_action)(t_philo *self, t_state state);
	long					(*get_time)(void);
	void					(*sleep_ms)(t_philo *self, long duration_ms);
	int						(*take_forks)(t_philo *self);
	void					(*drop_forks)(t_philo *self);
	void					(*lock_acquire)(void *lock);
	void					(*lock_release)(void *lock);
	bool					(*should_stop)(t_philo *self);
};

int							domain_philo_routine(t_philo *philo);
int							domain_philo_eat(t_philo *philo);

#endif
