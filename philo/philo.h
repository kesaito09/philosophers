/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 20:41:06 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/15 16:15:00 by codex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "philo_sync.h"
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define SUCCESS 1
# define FAILURE -1
# define UNSET_MUST_EAT -1

typedef struct s_info
{
	int			num_of_philo;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		num_must_eat;
	long		start_time;
	bool		is_stop_sim;
	t_lock		state_lock;
	t_lock		write_lock;
	t_lock		*forks;
}				t_info;

typedef struct s_philo
{
	int			id;
	long		eat_count;
	long		time_last_eat;
	pthread_t	thread;
	t_lock		*left_fork;
	t_lock		*right_fork;
	t_lock		last_eat_lock;
	t_info		*info;
}				t_philo;

typedef enum e_state
{
	TAKE,
	EAT,
	SLEEP,
	THINK,
	DIE,
}				t_state;

/* parse */
int				parse_input(int ac, char **av, t_info *info);

/* setup */
t_info			*init_info(int ac, char **av);
t_philo			*init_philo(t_info *info);
t_lock			*init_forks(int n);
int				initializer(int ac, char **av, t_philo **philos, t_info **info);
void			destroy_simulation(t_philo *philos, t_info *info);

/* simulation */
int				start_simulation(t_philo *philos, t_info *info);
int				monitoring(t_philo *philos, t_info *info);
void			*philo_routine(void *arg);
int				philo_take_forks(t_philo *philo, t_lock **first,
					t_lock **second);
void			philo_release_forks(t_lock *first, t_lock *second);

/* logger */
int				logger(t_philo *philo, t_state state);

/* state/time */
long			get_time_now(void);
int				philo_usleep(t_philo *philo, long duration_ms);
bool			is_simulation_finished(t_philo *philo);
void			set_simulation_stop(t_info *info);

/* mini-lib */
int				ft_atoi(const char *nptr);
void			*ft_calloc(size_t nmemb, size_t size);

#endif
