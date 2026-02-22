/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 20:20:00 by codex             #+#    #+#             */
/*   Updated: 2026/02/22 20:20:00 by codex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "setup_contract.h"

static void	destroy_philos(t_philo *philos, t_info *info)
{
	int	i;

	if (!philos || !info)
		return ;
	i = 0;
	while (i < info->num_of_philo)
	{
		if (philos[i].sem_meal)
			sem_close(philos[i].sem_meal);
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
	destroy_philos(philos, info);
	destroy_info(info);
}
