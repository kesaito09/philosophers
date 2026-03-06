/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_setup_philo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 13:02:31 by kesaitou          #+#    #+#             */
/*   Updated: 2026/03/06 13:02:31 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_infra.h"
#include "../include/philo_presentation.h"

static void	init_common_philo(t_philo_handler *handler, t_info *info, int index)
{
	handler->philo.id = index + 1;
	handler->philo.eat_count = 0;
	handler->philo.time_last_eat = 0;
	handler->philo.rule = &info->rule;
	handler->philo.ops = get_domain_ops();
	handler->info = info;
}

static int	init_handler_resources(t_philo_handler *handler,
		t_info *info, int index)
{
	handler->left_fork = info->forks[index];
	handler->right_fork = info->forks[(index + 1) % info->rule.num_of_philo];
	if (infra_init_philo_lock(handler) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int	init_single_philo(t_philo_handler *handler, t_info *info, int index)
{
	init_common_philo(handler, info, index);
	return (init_handler_resources(handler, info, index));
}

t_philo_handler	*init_philo(t_info *info)
{
	t_philo_handler	*philos;
	int				i;

	if (!info)
		return (NULL);
	philos = ft_calloc((size_t)info->rule.num_of_philo,
			sizeof(t_philo_handler));
	if (!philos)
		return (NULL);
	i = 0;
	while (i < info->rule.num_of_philo)
	{
		if (init_single_philo(&philos[i], info, i) == FAILURE)
			return (destroy_philos_by_count(philos, i), NULL);
		i++;
	}
	return (philos);
}
