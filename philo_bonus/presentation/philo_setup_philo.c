/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_setup_philo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 05:42:09 by kesaitou          #+#    #+#             */
/*   Updated: 2026/03/06 00:00:00 by kesaitou         ###   ########.fr       */
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

static int	init_meal_lock(t_philo_handler *h)
{
	sem_t	*meal_lock;

	h->meal_sem_name = build_meal_sem_name(h->philo.id);
	if (!h->meal_sem_name)
		return (FAILURE);
	meal_lock = sem_open_wrapper(h->meal_sem_name, 1);
	if (!meal_lock)
	{
		free(h->meal_sem_name);
		h->meal_sem_name = NULL;
		return (FAILURE);
	}
	h->last_eat_lock = meal_lock;
	return (SUCCESS);
}

static void	init_common_philo(t_philo_handler *handler, t_info *info, int index)
{
	handler->philo.id = index + 1;
	handler->philo.eat_count = 0;
	handler->philo.time_last_eat = 0;
	handler->philo.rule = &info->rule;
	handler->philo.ops = get_domain_ops();
	handler->info = info;
}

static int	init_single_philo(t_philo_handler *handler,
		t_info *info, int index)
{
	init_common_philo(handler, info, index);
	return (init_meal_lock(handler));
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
