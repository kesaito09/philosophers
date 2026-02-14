/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 20:41:06 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/15 05:39:40 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _DEFAULT_SOURCE
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/time.h>
#include <stdbool.h>

#define SUCCESS 1
#define FAILUER -1

typedef struct s_info
{
    int             num_of_philo;
    long            time_to_die;
    long            time_to_eat;
    long            time_to_sleep;
    long            num_must_eat;
    long            start_time;
	bool			is_stop_sim;
	pthread_mutex_t	state_lock;
    pthread_mutex_t write_lock;
    pthread_mutex_t *forks;
    
}   t_info;

typedef struct s_philo
{
    int				id;
    int				eat_count;
    long			time_last_eat;
    pthread_t		thread;
    pthread_mutex_t	*left_fork;
    pthread_mutex_t	*right_fork;
    pthread_mutex_t last_eat_lock;
    t_info			info;

}   t_philo;

typedef enum e_state
{
    TAKE,
    EAT,
    SLEEP,
    THINK,
    DIE,
}	t_state;

/*philo_setup_*/
t_info	*init_info(int ac, char **av);
t_philo	*init_philo(t_info *info);
pthread_mutex_t	*init_forks(int n);

int	initializer(int ac, char **av);





/*philo_utils1_lib*/
int	    ft_atoi(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);

/*philo_utils2_*/
long	get_time_now(void);
bool	is_simulation_finished(t_philo *philo);
int		logger(t_philo *philo, t_state state);

