/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 05:48:32 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/27 05:48:34 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_infra.h"
#include "../include/philo_presentation.h"
#include <stdlib.h>

void	destroy_philos_by_count(t_philo *philos, int count)
{
	int	i;

	if (!philos)
		return ;
	i = 0;
	while (i < count)
	{
		if (philos[i].last_eat_lock)
			sem_close((sem_t *)philos[i].last_eat_lock);
		if (philos[i].meal_sem_name)
		{
			sem_unlink_wrapper(philos[i].meal_sem_name);
			free(philos[i].meal_sem_name);
		}
		i++;
	}
	free(philos);
}

static void	destroy_info(t_info *info)
{
	if (!info)
		return ;
	cleanup_semaphores(info);
	free(info->pids);
	free(info);
}

void	destroy_simulation(t_philo *philos, t_info *info)
{
	if (info)
		destroy_philos_by_count(philos, info->num_of_philo);
	destroy_info(info);
}
