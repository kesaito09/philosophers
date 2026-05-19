/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 12:00:00 by kesaitou          #+#    #+#             */
/*   Updated: 2026/05/20 08:57:46 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stddef.h>

# define UNSET_MUST_EAT -1

typedef enum e_status
{
	SUCCESS = 0,
	FAILURE = 1,
	STOPPED = 2,
	DIED = 3,
	SATED = 4
}						t_status;

typedef enum e_state
{
	STATE_TAKE_FORK,
	STATE_EAT,
	STATE_SLEEP,
	STATE_THINK,
	STATE_DIE
}						t_state;

typedef struct s_rule
{
	int					num_of_philo;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				num_must_eat;
}						t_rule;

typedef struct s_sim_state
{
	long				start_time;
	bool				is_stopped;
	pthread_mutex_t		state_lock;
	pthread_mutex_t		write_lock;
}						t_sim_state;

typedef struct s_meal
{
	long				count;
	long				last_time;
	pthread_mutex_t		lock;
}						t_meal;

typedef struct s_info	t_info;

typedef struct s_philo
{
	int					id;
	pthread_t			thread;
	t_meal				meal;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_info				*info;
}						t_philo;

struct					s_info
{
	t_rule				rule;
	t_sim_state			sim;
	pthread_mutex_t		*forks;
	t_philo				*philos;
};

int						parse_input(int ac, char **av, t_rule *rule);

int						init_simulation(int ac, char **av, t_info *info);
void					destroy_simulation(t_info *info);

void					*philo_routine(void *arg);
int						take_forks(t_philo *philo);
void					drop_forks(t_philo *philo);

int						start_simulation(t_info *info);
int						monitor_loop(t_info *info);
int						log_action(t_philo *philo, t_state state);

long					get_time_ms(void);
int						philo_usleep(t_philo *philo, long duration_ms);
void					*ft_calloc(size_t nmemb, size_t size);
bool					is_stopped(t_info *info);
void					stop_simulation(t_info *info);

#endif
