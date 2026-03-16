/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_domain.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 04:55:39 by kesaitou          #+#    #+#             */
/*   Updated: 2026/03/06 00:00:00 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_DOMAIN_H
# define PHILO_DOMAIN_H

# include <stdbool.h>
# define SUCCESS 1
# define FAILURE -1
# define UNSET_MUST_EAT -1

typedef struct s_sim_rule	t_sim_rule;
typedef struct s_philo		t_philo;
typedef struct s_domain_ops	t_domain_ops;
typedef bool				(*t_philo_bool_op)(t_philo *self);

typedef enum e_state
{
	STATE_TAKE_FORK,
	STATE_EAT,
	STATE_SLEEP,
	STATE_THINK,
	STATE_DIE,
}							t_state;

struct						s_sim_rule
{
	int						num_of_philo;
	long					time_to_die;
	long					time_to_eat;
	long					time_to_sleep;
	long					num_must_eat;
};

struct						s_philo
{
	int						id;
	long					eat_count;
	long					time_last_eat;
	t_sim_rule				*rule;
	t_domain_ops			*ops;
};

struct						s_domain_ops
{
	int						(*take_forks)(t_philo *self);
	void					(*drop_forks)(t_philo *self);
	int						(*log_action)(t_philo *self, t_state state);
	int						(*update_meal)(t_philo *self);
	t_philo_bool_op			is_sated;
	t_philo_bool_op			should_stop;
	long					(*last_meal_ms)(t_philo *self);
	long					(*now_ms)(void);
	int						(*sleep_ms)(t_philo *self, long duration_ms);
};

int							domain_philo_routine(t_philo *philo);

#endif
