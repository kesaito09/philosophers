/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 17:08:27 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/14 17:15:34 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	take_forks()
{
	
	
	
}

void	*philo_eat(t_philo philo)
{
	pthread_mutex_lock(philo.left_fork);
	pthread_mutex_lock(philo.right_fork);
	usleep(philo.info.time_to_eat);
	pthread_mutex_unlock(philo.left_fork);
	pthread_mutex_unlock(philo.right_fork);
}

