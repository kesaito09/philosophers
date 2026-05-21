/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 12:00:00 by kesaitou          #+#    #+#             */
/*   Updated: 2026/05/21 00:00:00 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <string.h>

static void	link_forks(t_info *info);

int	init_simulation(int ac, char **av, t_info *info)
{
	memset(info, 0, sizeof(t_info));
	if (parse_input(ac, av, &info->rule) == FAILURE)
		return (FAILURE);
	info->forks = ft_calloc(info->rule.num_of_philo,
			sizeof(pthread_mutex_t));
	info->philos = ft_calloc(info->rule.num_of_philo, sizeof(t_philo));
	if (!info->forks || !info->philos || init_locks(info) == FAILURE)
	{
		free(info->forks);
		free(info->philos);
		info->forks = NULL;
		info->philos = NULL;
		return (FAILURE);
	}
	link_forks(info);
	return (SUCCESS);
}

void	destroy_simulation(t_info *info)
{
	if (!info)
		return ;
	destroy_all_mutexes(info);
	free(info->forks);
	free(info->philos);
	info->forks = NULL;
	info->philos = NULL;
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
