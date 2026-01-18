/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 20:41:06 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/18 21:29:40 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>
#include  <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

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
    int             dead_flag;
    pthread_mutex_t dead_lock;
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
    t_info			*info;

}   t_philo;








/*philo_utils*/
int	    ft_atoi(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);

