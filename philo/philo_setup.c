/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 19:55:06 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/15 16:15:00 by codex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_forks(pthread_mutex_t *forks, int count)
{
	int	i;

	if (!forks)
		return ;
	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
}

static int	init_forks_mutexes(pthread_mutex_t *forks, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			destroy_forks(forks, i);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

pthread_mutex_t	*init_forks(int n)
{
	pthread_mutex_t	*forks;

	forks = ft_calloc((size_t)n, sizeof(pthread_mutex_t));
	if (!forks)
		return (NULL);
	if (init_forks_mutexes(forks, n) == FAILURE)
		return (NULL);
	return (forks);
}

static int	init_info_locks(t_info *info)
{
	if (pthread_mutex_init(&info->state_lock, NULL) != 0)
		return (FAILURE);
	if (pthread_mutex_init(&info->write_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&info->state_lock);
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	init_info_resources(t_info *info)
{
	if (init_info_locks(info) == FAILURE)
		return (FAILURE);
	info->forks = init_forks(info->num_of_philo);
	if (!info->forks)
	{
		pthread_mutex_destroy(&info->state_lock);
		pthread_mutex_destroy(&info->write_lock);
		return (FAILURE);
	}
	return (SUCCESS);
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

static int	init_single_philo(t_philo *philo, t_info *info, int index)
{
	philo->id = index + 1;
	philo->eat_count = 0;
	philo->time_last_eat = 0;
	philo->info = info;
	philo->left_fork = &info->forks[index];
	philo->right_fork = &info->forks[(index + 1) % info->num_of_philo];
	if (pthread_mutex_init(&philo->last_eat_lock, NULL) != 0)
		return (FAILURE);
	return (SUCCESS);
}

static void	destroy_philo_locks(t_philo *philos, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&philos[i].last_eat_lock);
		i++;
	}
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

int	initializer(int ac, char **av, t_philo **philos, t_info **info)
{
	if (!philos || !info)
		return (FAILURE);
	*info = init_info(ac, av);
	if (!*info)
		return (FAILURE);
	*philos = init_philo(*info);
	if (!*philos)
	{
		destroy_simulation(NULL, *info);
		*info = NULL;
		return (FAILURE);
	}
	set_initial_meal_times(*philos, *info);
	return (SUCCESS);
}

static void	destroy_philos(t_philo *philos, t_info *info)
{
	if (!philos || !info)
		return ;
	destroy_philo_locks(philos, info->num_of_philo);
	free(philos);
}

static void	destroy_info(t_info *info)
{
	if (!info)
		return ;
	destroy_forks(info->forks, info->num_of_philo);
	pthread_mutex_destroy(&info->state_lock);
	pthread_mutex_destroy(&info->write_lock);
	free(info);
}

void	destroy_simulation(t_philo *philos, t_info *info)
{
	destroy_philos(philos, info);
	destroy_info(info);
}
