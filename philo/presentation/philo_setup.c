/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 22:36:05 by kesaitou          #+#    #+#             */
/*   Updated: 2026/03/02 18:09:43 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_infra.h"
#include "../include/philo_presentation.h"
#include <stdlib.h>

static int	init_info_resources(t_info *info)
{
	if (infra_init_info_locks(info) == FAILURE)
		return (FAILURE);
	info->forks = infra_create_forks(info->rule.num_of_philo);
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

static int	init_single_philo(t_philo_handler *handler, t_info *info, int index)
{
	handler->philo.id = index + 1;
	handler->philo.eat_count = 0;
	handler->philo.time_last_eat = 0;
	handler->philo.rule = &info->rule;
	handler->philo.ops = get_domain_ops();
	handler->info = info;
	handler->left_fork = info->forks[index];
	handler->right_fork = info->forks[(index + 1) % info->rule.num_of_philo];
	if (infra_init_philo_lock(handler) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

t_philo_handler	*init_philo(t_info *info)
{
	t_philo_handler	*philos;
	int			i;

	philos = ft_calloc((size_t)info->rule.num_of_philo, sizeof(t_philo_handler));
	if (!philos)
		return (NULL);
	i = 0;
	while (i < info->rule.num_of_philo)
	{
		if (init_single_philo(&philos[i], info, i) == FAILURE)
			return (infra_destroy_philo_locks(philos, i), free(philos), NULL);
		i++;
	}
	return (philos);
}
