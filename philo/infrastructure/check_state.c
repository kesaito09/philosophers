/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 03:18:11 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/15 03:21:50 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	is_simulation_finished(t_philo *philo)
{
	bool	flag;

	pthread_mutex_lock(&philo->info.state_lock);
	flag = philo->info.is_stop_sim;
	pthread_mutex_unlock(&philo->info.state_lock);
	return (flag);
}

