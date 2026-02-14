/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:41:32 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/14 16:17:58 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


void	*philo_eat(t_philo philo, t_info info)
{
	pthread_mutex_lock(philo.left_fork);
	pthread_mutex_lock(philo.right_fork);
	usleep(info.time_to_eat);
	pthread_mutex_unlock(philo.left_fork);
	pthread_mutex_unlock(philo.right_fork);
}

void	*routine(t_philo philo, t_info info)
{

	
	
	
	
	
	
	
}


/*
哲学者の行動
mutex_lock(forks) →usleep(eat_time) 
→mutex_unlock(forks) →usleep(sleep_time) 
→usleep(think_time)となる。これをroutineにしてthreadを作成する。
*/









