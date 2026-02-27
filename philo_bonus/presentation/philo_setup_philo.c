/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_setup_philo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 05:42:09 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/27 05:47:39 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_infra.h"
#include "../include/philo_presentation.h"
#include <stdlib.h>

static char	*build_meal_sem_name(int id)
{
	char	*id_str;
	char	*name;

	id_str = ft_itoa(id);
	if (!id_str)
		return (NULL);
	name = ft_strjoin(SEM_MEAL_PREFIX, id_str);
	free(id_str);
	return (name);
}

static int	init_single_philo(t_philo *philo, t_info *info, int index)
{
	sem_t	*meal_lock;

	philo->id = index + 1;
	philo->eat_count = 0;
	philo->time_last_eat = 0;
	philo->info = info;
	philo->meal_sem_name = build_meal_sem_name(philo->id);
	if (!philo->meal_sem_name)
		return (FAILURE);
	meal_lock = sem_open_wrapper(philo->meal_sem_name, 1);
	if (!meal_lock)
	{
		free(philo->meal_sem_name);
		philo->meal_sem_name = NULL;
		return (FAILURE);
	}
	philo->last_eat_lock = meal_lock;
	philo->ops = get_domain_ops();
	return (SUCCESS);
}

t_philo	*init_philo(t_info *info)
{
	t_philo	*philos;
	int		i;

	if (!info)
		return (NULL);
	philos = ft_calloc((size_t)info->num_of_philo, sizeof(t_philo));
	if (!philos)
		return (NULL);
	i = 0;
	while (i < info->num_of_philo)
	{
		if (init_single_philo(&philos[i], info, i) == FAILURE)
			return (destroy_philos_by_count(philos, i), NULL);
		i++;
	}
	return (philos);
}
