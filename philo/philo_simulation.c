/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 05:27:13 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/15 16:15:00 by codex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	join_philosophers_thread(t_philo *philos, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philo)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

static int	create_philosophers_thread(t_philo *philos, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philo)
	{
		if (pthread_create(&philos[i].thread, NULL, philo_routine,
				&philos[i]) != 0)
		{
			set_simulation_stop(info);
			while (--i >= 0)
				pthread_join(philos[i].thread, NULL);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

int	start_simulation(t_philo *philos, t_info *info)
{
	if (create_philosophers_thread(philos, info) == FAILURE)
		return (FAILURE);
	monitoring(philos, info);
	if (join_philosophers_thread(philos, info) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
