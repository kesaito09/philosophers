/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 12:00:00 by kesaitou          #+#    #+#             */
/*   Updated: 2026/05/17 14:00:00 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <string.h>

static int	init_locks(t_info *info);
static void	destroy_locks(t_info *info);
static void	link_forks(t_info *info);

int	init_simulation(int ac, char **av, t_info *info)
{
	memset(info, 0, sizeof(t_info));
	if (parse_input(ac, av, &info->rule) == FAILURE)
		return (FAILURE);
	info->forks = ft_calloc(info->rule.num_of_philo,
			sizeof(pthread_mutex_t));
	info->philos = ft_calloc(info->rule.num_of_philo, sizeof(t_philo));
	if (!info->forks || !info->philos)
	{
		destroy_simulation(info);
		return (FAILURE);
	}
	if (init_locks(info) == FAILURE)
	{
		destroy_simulation(info);
		return (FAILURE);
	}
	link_forks(info);
	return (SUCCESS);
}

void	destroy_simulation(t_info *info)
{
	if (!info)
		return ;
	destroy_locks(info);
	free(info->forks);
	free(info->philos);
	info->forks = NULL;
	info->philos = NULL;
}

static int	init_locks(t_info *info)
{
	int	i;

	if (pthread_mutex_init(&info->sim.state_lock, NULL) != 0)
		return (FAILURE);
	if (pthread_mutex_init(&info->sim.write_lock, NULL) != 0)
		return (pthread_mutex_destroy(&info->sim.state_lock), FAILURE);
	i = 0;
	while (i < info->rule.num_of_philo)
	{
		if (pthread_mutex_init(&info->forks[i], NULL) != 0)
			return (FAILURE);
		if (pthread_mutex_init(&info->philos[i].meal.lock, NULL) != 0)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

static void	destroy_locks(t_info *info)
{
	int	i;

	i = 0;
	while (info->forks && i < info->rule.num_of_philo)
	{
		pthread_mutex_destroy(&info->forks[i]);
		pthread_mutex_destroy(&info->philos[i].meal.lock);
		i++;
	}
	pthread_mutex_destroy(&info->sim.state_lock);
	pthread_mutex_destroy(&info->sim.write_lock);
}

static void	link_forks(t_info *info)
{
	int	i;
	int	n;

	n = info->rule.num_of_philo;
	i = 0;
	while (i < n)
	{
		info->philos[i].id = i + 1;
		info->philos[i].info = info;
		info->philos[i].left_fork = &info->forks[i];
		info->philos[i].right_fork = &info->forks[(i + 1) % n];
		i++;
	}
}
