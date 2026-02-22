/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_contract.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 20:20:00 by codex             #+#    #+#             */
/*   Updated: 2026/02/22 21:42:15 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETUP_CONTRACT_H
# define SETUP_CONTRACT_H

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# define SUCCESS 1
# define FAILURE -1
# define UNSET_MUST_EAT -1
# define EXIT_DONE 0
# define EXIT_DEAD 1
# define SEM_FORKS "/forks"
# define SEM_SIT "/sit"
# define SEM_WRITE "/write"
# define SEM_STATE "/state"
# define SEM_MEAL_PREFIX "/meal_"

typedef struct s_info
{
	pid_t			*pids;
	int				num_of_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			num_must_eat;
	long			start_time;
	bool			is_stop_sim;
	sem_t			*forks;
	sem_t			*sem_sit;
	sem_t			*sem_write;
	sem_t			*sem_state;
}	t_info;

typedef struct s_philo
{
	int				id;
	long			eat_count;
	long			time_last_eat;
	sem_t			*sem_meal;
	char			*meal_sem_name;
	t_info			*info;
}	t_philo;

typedef enum e_state
{
	TAKE,
	EAT,
	SLEEP,
	THINK,
	DIE,
}	t_state;

int			parse_input(int ac, char **av, t_info *info);
int			initialize_simulation(int ac, char **av, t_philo **philos,
				t_info **info);
void		destroy_simulation(t_philo *philos, t_info *info);
t_philo		*init_philo(t_info *info);

int			start_simulation(t_philo *philos, t_info *info);

int			child_runtime(t_philo *philo);
int			philo_routine(t_philo *philo);
int			philo_eat(t_philo *philo);
bool		is_simulation_finished(t_philo *philo);
void		set_simulation_stop(t_info *info);

sem_t		*sem_open_wrapper(char *sem_name, int n);
int			sem_unlink_wrapper(char *sem_name);
int			cleanup_semaphores(t_info *info);
long		get_time_now(void);
int			philo_usleep(t_philo *philo, long duration_ms);
int			logger(t_philo *philo, t_state state);

void		*ft_calloc(size_t nmemb, size_t size);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memset(void *s, int c, size_t n);
size_t		ft_strlen(const char *str);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_itoa(int n);
char		*ft_strdup(const char *s);

#endif
