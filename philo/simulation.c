/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 12:00:00 by kesaitou          #+#    #+#             */
/*   Updated: 2026/05/21 19:31:49 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_initial_meal_times(t_info *info);
static int	create_threads(t_info *info);
static void	join_threads(t_info *info);

int	start_simulation(t_info *info)
{
	if (!info)
		return (FAILURE);
	set_initial_meal_times(info);
	if (create_threads(info) == FAILURE)
		return (FAILURE);
	monitor_loop(info);
	join_threads(info);
	return (SUCCESS);
}

static void	set_initial_meal_times(t_info *info)
{
	int	i;

	info->sim.start_time = get_time_ms();
	i = 0;
	while (i < info->rule.num_of_philo)
	{
		info->philos[i].meal.last_time = info->sim.start_time;
		i++;
	}
}

static int	create_threads(t_info *info)
{
	int	i;
	int	j;

	i = 0;
	while (i < info->rule.num_of_philo)
	{
		if (pthread_create(&info->philos[i].thread, NULL,
				philo_routine, &info->philos[i]) != PTHREAD_OK)
		{
			stop_simulation(info);
			j = 0;
			while (j < i)
			{
				pthread_join(info->philos[j].thread, NULL);
				j++;
			}
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

static void	join_threads(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->rule.num_of_philo)
	{
		pthread_join(info->philos[i].thread, NULL);
		i++;
	}
}
