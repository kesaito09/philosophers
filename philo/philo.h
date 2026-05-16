/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 00:00:00 by kesaitou          #+#    #+#             */
/*   Updated: 2026/05/16 00:00:00 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define UNSET_MUST_EAT -1

typedef enum e_state
{
	STATE_TAKE_FORK,
	STATE_EAT,
	STATE_SLEEP,
	STATE_THINK,
	STATE_DIE,
}					t_state;

typedef struct s_rule
{
	int				num;
	long			t_die;
	long			t_eat;
	long			t_sleep;
	long			must_eat;
}					t_rule;

struct				s_sim;

typedef struct s_philo
{
	int				id;
	long			eat_count;
	long			last_eat_ms;
	pthread_mutex_t	meal_lock;
	pthread_t		thread;
	struct s_sim	*sim;
}					t_philo;

typedef struct s_sim
{
	t_rule			rule;
	long			start_ms;
	bool			stop;
	pthread_mutex_t	stop_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}					t_sim;

/* parse.c */
int					parse_args(int ac, char **av, t_rule *rule);

/* init.c */
int					sim_init(t_sim *sim, const t_rule *rule);
void				sim_destroy(t_sim *sim);

/* routine.c */
int					start_simulation(t_sim *sim);
void				*philo_routine(void *arg);

/* monitor.c */
int					monitor(t_sim *sim);

/* utils.c */
long				get_time_ms(void);
int					smart_sleep(t_philo *philo, long duration_ms);
void				print_action(t_philo *philo, t_state state);
bool				sim_stopped(t_sim *sim);
void				sim_set_stop(t_sim *sim);

#endif
