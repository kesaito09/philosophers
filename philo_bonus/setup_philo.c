/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 20:20:00 by codex             #+#    #+#             */
/*   Updated: 2026/02/22 21:42:15 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "setup_contract.h"

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
	philo->id = index + 1;
	philo->eat_count = 0;
	philo->time_last_eat = 0;
	philo->info = info;
	philo->meal_sem_name = build_meal_sem_name(philo->id);
	if (!philo->meal_sem_name)
		return (FAILURE);
	philo->sem_meal = sem_open_wrapper(philo->meal_sem_name, 1);
	if (!philo->sem_meal)
	{
		free(philo->meal_sem_name);
		philo->meal_sem_name = NULL;
		return (FAILURE);
	}
	return (SUCCESS);
}

static void	destroy_partial_philos(t_philo *philos, int count)
{
	int	i;

	if (!philos)
		return ;
	i = 0;
	while (i < count)
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
			return (destroy_partial_philos(philos, i), NULL);
		i++;
	}
	return (philos);
}
