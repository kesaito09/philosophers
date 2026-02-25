/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_types.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:54:55 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/25 16:55:07 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TYPES_H
# define PHILO_TYPES_H
# include "philo_domain.h"
# include <pthread.h>
# include <stdbool.h>
# define SUCCESS 1
# define FAILURE -1
# define UNSET_MUST_EAT -1

typedef struct s_info
{
	int				num_of_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			num_must_eat;
	long			start_time;
	bool			is_stop_sim;
	void			*state_lock;
	void			*write_lock;
	void			**forks;
}					t_info;

typedef struct s_philo
{
	int				id;
	long			eat_count;
	long			time_last_eat;
	pthread_t		thread;
	void			*left_fork;
	void			*right_fork;
	void			*last_eat_lock;
	t_info			*info;
	t_domain_ops	*ops;
}					t_philo;
#endif
