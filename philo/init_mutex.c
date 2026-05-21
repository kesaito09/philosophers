/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 00:00:00 by kesaitou          #+#    #+#             */
/*   Updated: 2026/05/21 00:00:00 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_n_mutexes(t_info *info, int n_forks, int n_meals);

int	init_locks(t_info *info)
{
	int	i;

	if (pthread_mutex_init(&info->sim.state_lock, NULL) != PTHREAD_OK)
		return (FAILURE);
	if (pthread_mutex_init(&info->sim.write_lock, NULL) != PTHREAD_OK)
	{
		pthread_mutex_destroy(&info->sim.state_lock);
		return (FAILURE);
	}
	i = 0;
	while (i < info->rule.num_of_philo)
	{
		if (pthread_mutex_init(&info->forks[i], NULL) != PTHREAD_OK)
			return (destroy_n_mutexes(info, i, i), FAILURE);
		if (pthread_mutex_init(&info->philos[i].meal.lock, NULL) != PTHREAD_OK)
			return (destroy_n_mutexes(info, i + 1, i), FAILURE);
		i++;
	}
	return (SUCCESS);
}

void	destroy_all_mutexes(t_info *info)
{
	int	n;

	if (!info->forks)
		return ;
	n = info->rule.num_of_philo;
	destroy_n_mutexes(info, n, n);
}

static void	destroy_n_mutexes(t_info *info, int n_forks, int n_meals)
{
	int	i;

	i = 0;
	while (i < n_forks)
	{
		pthread_mutex_destroy(&info->forks[i]);
		i++;
	}
	i = 0;
	while (i < n_meals)
	{
		pthread_mutex_destroy(&info->philos[i].meal.lock);
		i++;
	}
	pthread_mutex_destroy(&info->sim.state_lock);
	pthread_mutex_destroy(&info->sim.write_lock);
}
