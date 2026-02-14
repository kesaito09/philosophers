/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 22:56:37 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/15 01:59:19 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static char	*get_message(t_state state)
{
	if (state == TAKE)
        return ("has taken a fork");
    else if (state == EAT)
        return ("is eating");
    else if (state == SLEEP)
        return ("is sleeping");
    else if (state == THINK)
        return ("is thinking");
    else if (state == DIE)
        return ("died");
    return ("error");
}

int	logger(t_philo *philo, t_state state)
{
	char	*msg;
	long	time;

	pthread_mutex_lock(&philo ->info.write_flag);
	if (is_dead(philo) && state != DIE)
	{
		pthread_mutex_unlock(&philo->info.write_flag);
		return (FAILUER);
	}
	time = get_time_now() - philo->info.start_time;
	msg = get_message(state);
	printf("%ld %d %s\n",time, philo->id, msg);
	pthread_mutex_unlock(&philo->info.write_flag);
	return (SUCCESS);
}

int init_info_mutex_tester(t_info *info, int n)
{
	info->forks = init_forks(n);
	if (!info->forks)
		return (free(info), FAILUER);
	if (pthread_mutex_init(&info->dead_flag, NULL) != 0)
		return (FAILUER);
	if (pthread_mutex_init(&info->write_flag, NULL) != 0)
		return (FAILUER);
	return (SUCCESS);
}

t_info	*init_info_tester(int n)
{
	t_info	*info;

	info = ft_calloc(sizeof(t_info), 1);
	if (!info)
		return (NULL);
	info->num_of_philo = n;
	info->time_to_die = 4;
	info->time_to_eat = 4;
	info->time_to_sleep = 4;
	info->num_must_eat = 4;
	if (init_info_mutex_tester(info, n) == FAILUER)
		return (NULL);
	return (info);
}

// int main(int ac, char **av)
// {
// 	t_info	*info;
// 	t_philo	*philo;

// 	info = init_info_tester(4);
	
// }
