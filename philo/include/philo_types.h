/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_types.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:54:55 by kesaitou          #+#    #+#             */
/*   Updated: 2026/03/02 18:03:32 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TYPES_H
# define PHILO_TYPES_H
# include "./philo_domain.h"
# include <pthread.h>

typedef struct s_info
{
	t_sim_rule		rule;
	long			start_time;
	bool			is_stop_sim;
	void			*state_lock;
	void			*write_lock;
	void			**forks;
}					t_info;

typedef struct s_philo_handler
{
	t_philo			philo;
	pthread_t		thread;
	void			*left_fork;
	void			*right_fork;
	void			*last_eat_lock;
	t_info			*info;
}					t_philo_handler;

#endif
