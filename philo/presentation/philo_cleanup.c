/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:39:15 by kesaitou          #+#    #+#             */
/*   Updated: 2026/03/03 22:10:52 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_infra.h"
#include "../include/philo_presentation.h"
#include <stdlib.h>

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

static void	destroy_philos(t_philo_handler *philos, t_info *info)
{
	if (!philos || !info)
		return ;
	infra_destroy_philo_locks(philos, info->rule.num_of_philo);
	free(philos);
}

static void	destroy_info(t_info *info)
{
	if (!info)
		return ;
	infra_destroy_forks(info->forks, info->rule.num_of_philo);
	infra_destroy_info_locks(info);
	free(info);
}

void	destroy_simulation(t_philo_handler *philos, t_info *info)
{
	destroy_philos(philos, info);
	destroy_info(info);
}
