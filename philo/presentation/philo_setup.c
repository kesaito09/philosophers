/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 22:36:05 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/28 15:15:20 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_infra.h"
#include "../include/philo_presentation.h"
#include <stdlib.h>

static int	init_info_resources(t_info *info)
{
	if (infra_init_info_locks(info) == FAILURE)
		return (FAILURE);
	info->forks = infra_create_forks(info->num_of_philo);
	if (!info->forks)
	{
		infra_destroy_info_locks(info);
		return (FAILURE);
	}
	return (SUCCESS);
}

t_info	*init_info(int ac, char **av)
{
	t_info	*info;

	info = ft_calloc(1, sizeof(t_info));
	if (!info)
		return (NULL);
	if (parse_input(ac, av, info) == FAILURE)
		return (free(info), NULL);
	if (init_info_resources(info) == FAILURE)
		return (free(info), NULL);
	info->is_stop_sim = false;
	info->start_time = 0;
	return (info);
}

static int	init_single_philo(t_philo *philo, t_info *info, int index)
{
	philo->id = index + 1;
	philo->eat_count = 0;
	philo->time_last_eat = 0;
	philo->info = info;
	philo->left_fork = info->forks[index];
	philo->right_fork = info->forks[(index + 1) % info->num_of_philo];
	philo->ops = get_domain_ops();
	if (infra_init_philo_lock(philo) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

t_philo	*init_philo(t_info *info)
{
	t_philo	*philos;
	int		i;

	philos = ft_calloc((size_t)info->num_of_philo, sizeof(t_philo));
	if (!philos)
		return (NULL);
	i = 0;
	while (i < info->num_of_philo)
	{
		if (init_single_philo(&philos[i], info, i) == FAILURE)
			return (infra_destroy_philo_locks(philos, i), free(philos), NULL);
		i++;
	}
	return (philos);
}
