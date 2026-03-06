/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 05:45:14 by kesaitou          #+#    #+#             */
/*   Updated: 2026/03/06 00:00:00 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_presentation.h"
#include "../include/philo_infra.h"
#include <stdlib.h>

static int	init_info_resources(t_info *info)
{
	int	sit_slots;

	sit_slots = info->rule.num_of_philo / 2;
	if (sit_slots <= 0)
		sit_slots = 1;
	info->forks = sem_open_wrapper(SEM_FORKS, info->rule.num_of_philo);
	if (!info->forks)
		return (FAILURE);
	info->sem_sit = sem_open_wrapper(SEM_SIT, sit_slots);
	if (!info->sem_sit)
		return (cleanup_semaphores(info), FAILURE);
	info->write_lock = sem_open_wrapper(SEM_WRITE, 1);
	if (!info->write_lock)
		return (cleanup_semaphores(info), FAILURE);
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
	info->state_lock = sem_open_wrapper(SEM_STATE, 1);
	if (!info->state_lock)
		return (free(info), NULL);
	if (init_info_resources(info) == FAILURE)
		return (cleanup_semaphores(info), free(info), NULL);
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

int	initializer(int ac, char **av, t_philo_handler **ph, t_info **info)
{
	if (!ph || !info)
		return (FAILURE);
	*info = init_info(ac, av);
	if (!*info)
		return (FAILURE);
	*ph = init_philo(*info);
	if (!*ph)
		return (destroy_simulation(NULL, *info), *info = NULL, FAILURE);
	(*info)->pids = ft_calloc((size_t)(*info)->rule.num_of_philo,
			sizeof(pid_t));
	if (!(*info)->pids)
	{
		destroy_simulation(*ph, *info);
		*ph = NULL;
		*info = NULL;
		return (FAILURE);
	}
	set_initial_meal_times(*ph, *info);
	return (SUCCESS);
}
