/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 18:26:12 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/16 23:39:27 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# define SUCCESS 1
# define FAILURE -1
# define UNSET_MUST_EAT -1
# define SEM_FORKS "/forks"
# define SEM_SIT "/sit"
# define SEM_WRITE "/write"
# define SEM_STOP "/stop"

typedef struct s_info
{
	pid_t	*pids;
	int		num_of_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	num_must_eat;
	long	start_time;
	bool	is_stop_sim;
	sem_t	*forks;
	sem_t	*sem_sit;
	sem_t	*sem_write;
	sem_t	*sem_stop;
}			t_info;

typedef struct s_philo
{
	int		id;
	long	eat_count;
	long	time_last_eat;
	sem_t	*sem_eat;
	t_info	*info;
}			t_philo;

typedef enum e_state
{
	TAKE,
	EAT,
	SLEEP,
	THINK,
	DIE,
}			t_state;

/* parse */
int			parse_input(int ac, char **av, t_info *info);
int			setup_philos(t_philo *philos, t_info	*info);


/* state/time */
long		get_time_now(void);
int			philo_usleep(t_philo *philo, long duration_ms);

/* mini-lib */
int			ft_atoi(const char *nptr);
void		*ft_calloc(size_t nmemb, size_t size);

#endif
