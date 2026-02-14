/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 22:23:40 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/14 17:15:28 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

pthread_mutex_t	*init_forks(int n)
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	forks = ft_calloc(sizeof(pthread_mutex_t) , n);
	if (!forks)
		return (NULL);
	while (i < n)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (free(forks), NULL);
		i++;
	}
	return (forks);
}

int init_tinfo_mutex(t_info *info, int n)
{
	info->forks = init_forks(n);
	if (!info->forks)
		return (free(info), FAILUER);
	if (pthread_mutex_init(&info->dead_flag, NULL) != 0)
		return (FAILUER);
	if (pthread_mutex_init(&info->write_flag, NULL) != 0)
		return (FAILUER);
	return (SUCCESS);
}

t_info	*init_info(int ac, char **av)
{
	t_info	*info;
	int		n;
	if (!av || !*av)
		return (NULL);
	n = ft_atoi(av[1]);
	info = ft_calloc(sizeof(t_info), 1);
	if (!info)
		return (NULL);
	info->num_of_philo = n;
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		info->num_must_eat = ft_atoi(av[5]);
	else
		info ->num_must_eat = -1;
	if (init_tinfo_mutex(info, n) == FAILUER)
		return ( NULL);
	return (info);
}

t_philo	*init_philo(t_info *info)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = ft_calloc(sizeof(t_philo), info->num_of_philo);
	if (!philo)
		return (NULL);
	while (i < info->num_of_philo)
	{
		philo[i].id = i + 1;
		philo[i].eat_count = 0;
		philo[i].info = *info;
		philo[i].left_fork = &info->forks[i];
		philo[i].right_fork = &info->forks[(i + 1) % info->num_of_philo];
		if (pthread_mutex_init(&philo[i].last_eat_lock, NULL) == FAILUER)
			return (NULL);
		i++;
	}
	return (philo);
}

