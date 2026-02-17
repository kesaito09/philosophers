/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 22:43:22 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/16 23:54:02 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	setup_philos(t_philo *philos, t_info *info)
{
	

	
	
	
	
	
}

static void	set_initial_meal_times(t_philo *philos, t_info *info)
{
	int	i;

	info->start_time = get_time_now();
	i = 0;
	while (i < info->num_of_philo)
	{
		philos[i].time_last_eat = info->start_time;
		i++;
	}
}

t_info	*init_info(int ac, char **av)
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

static char	*create_name(int id)
{
	char	*sem_name;

	sem_name = 
	
	
	
}

static int	init_single_philo(t_philo *philo, t_info *info, int index)
{
	char	*sem_name;

	philo->id = index + 1;
	philo->eat_count = 0;
	philo->time_last_eat = 0;
	philo->sem_eat = sem_open(SEM_EAT, O_CREAT, 0644, 1);
	philo->info = info;
	return (SUCCESS);
}



t_philo	*init_philo(t_info *info)
{
	t_philo	*philos;
	int		i;

	philos = ft_calloc((size_t)info->num_of_philo, sizeof(t_philo));
	if (!philos)
		return (NULL);
	i = 0;
	while (i < info->num_of_philo)
	{
		if (init_single_philo(&philos[i], info, i) == FAILURE)
		{
			destroy_philo_locks(philos, i);
			free(philos);
			return (NULL);
		}
		i++;
	}
	return (philos);
}

int	initializer(int ac, char **av, t_philo **philos, t_info **info)
{
	if (!philos || !info)
		return (FAILURE);
	*info = init_info(ac, av);
	if (!*info)
		return (FAILURE);
	*philos = init_philo(*info);
	
	set_initial_meal_times(*philos, *info);
	return (SUCCESS);
}

