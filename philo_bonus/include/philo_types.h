/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_types.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 04:56:10 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/27 08:30:47 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TYPES_H
# define PHILO_TYPES_H

# include "./philo_domain.h"
# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include <sys/types.h>

# define SUCCESS 1
# define FAILURE -1
# define UNSET_MUST_EAT -1

# define EXIT_DONE 0
# define EXIT_DEAD 1
# define EXIT_ERROR 2

# define SEM_FORKS "/forks"
# define SEM_SIT "/sit"
# define SEM_WRITE "/write"
# define SEM_STATE "/state"
# define SEM_MEAL_PREFIX "/meal_"

typedef struct s_info
{
	int				num_of_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			num_must_eat;
	long			start_time;
	bool			is_stop_sim;
	sem_t			*state_lock;
	sem_t			*write_lock;
	sem_t			*forks;
	sem_t			*sem_sit;
	pid_t			*pids;
}					t_info;

typedef struct s_philo
{
	int				id;
	long			eat_count;
	long			time_last_eat;
	void			*last_eat_lock;
	t_info			*info;
	t_domain_ops	*ops;
	char			*meal_sem_name;
}					t_philo;
#endif
