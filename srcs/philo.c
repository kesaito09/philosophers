/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 20:41:08 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/18 20:30:39 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

pthread_mutex_t	*init_forks(int n)
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	forks = ft_calloc(sizeof(pthread_mutex_t) , n + 1);
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

int init_mutex(t_info *info, int n)
{
	info->forks = init_forks(n);
	if (!info->forks)
		return (free(info), FAILUER);
	if (pthread_mutex_init(&info->dead_lock, NULL) != 0)
		return (FAILUER);
	if (pthread_mutex_init(&info->write_lock, NULL) != 0)
		return (FAILUER);
	return (SUCESS);	
}

t_info	*init_tinfo(int ac, char **av)
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
	if (init_mutex(info, n) == FAILUER)
		return ( NULL);
	return (info);
}


int main(int ac, char **av)
{
    t_info	*info;

	if (ac != 5 && ac != 6)
		return (1);
	info = init_tinfo(ac, av);
	if (!info)
		return (1);
	
    
    
    
    
}