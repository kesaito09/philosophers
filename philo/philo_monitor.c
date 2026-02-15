/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 05:27:16 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/15 08:10:37 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_philo_dead(t_philo *philo, t_info *info)
{
	long	last_time;

	pthread_mutex_lock(&philo->last_eat_lock);
	last_time = philo->time_last_eat;
	pthread_mutex_unlock(&philo->last_eat_lock);
	if (get_time_now() - last_time >= info->time_to_die)
		return (true);
	return (false);
}

void	stop_simulation(t_philo *philo, t_info *info)
{
	pthread_mutex_lock(&info->write_lock);
	pthread_mutex_lock(&info->state_lock);
	info->is_stop_sim = 1;
	pthread_mutex_unlock(&info->state_lock);
	printf("%ld %d died\n",get_time_now() - info->start_time, philo->id);
	pthread_mutex_unlock(&info->write_lock);
}

int check_all_philosophers(t_philo *philos, t_info *info)
{
	int		i;

	i = 0;
	while (i < info->num_of_philo)
	{
		if (is_philo_dead(&philos[i], info))
		{
			stop_simulation(&philos[i], info);
			return (1);
		}
		i++;
	}
	return (0);
}

int	monitering(t_philo *philos, t_info *info)
{
	while (1)
	{
		if (check_all_philosophers(philos, info) == 1)
			return (1);
		usleep(1000);
	}
	return (0);
}

/*
	モニターがしたいことは
	ｎ番目の哲学者が死んだかを判定する
	死んだらログを出して、シミュレーションを終了させる
	
	
*/