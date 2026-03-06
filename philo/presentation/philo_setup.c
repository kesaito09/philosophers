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

static t_info	*init_info(int ac, char **av)
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

static void	set_initial_meal_times(t_philo_handler *philos, t_info *info)
{
	int	i;

	info->start_time = get_time_now();
	i = 0;
	while (i < info->rule.num_of_philo)
	{
		philos[i].philo.time_last_eat = info->start_time;
		i++;
	}
}

int	initializer(int ac, char **av, t_philo_handler **philos, t_info **info)
{
	if (!philos || !info)
		return (FAILURE);
	*info = init_info(ac, av);
	if (!*info)
		return (FAILURE);
	*philos = init_philo(*info);
	if (!*philos)
		return (destroy_simulation(NULL, *info), *info = NULL, FAILURE);
	set_initial_meal_times(*philos, *info);
	return (SUCCESS);
}
