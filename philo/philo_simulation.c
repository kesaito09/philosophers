/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 05:27:13 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/15 08:02:26 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_philosophers_thread(t_philo *philos, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philo)
	{
		if (pthread_create(&philos[i].thread, NULL, philo_routine,
				&philos[i]) != 0)
			return (FAILUER);
		i++;
	}
	return (SUCCESS);
}

int join_philosophers_thread(t_philo *philos, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philo)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
			return (FAILUER);
		i++;
	}
	return (SUCCESS);
}

int	start_simulation(t_philo *philos, t_info *info)
{
	if (create_philosophers_thread(philos, info) == 1)
		return (FAILUER);
	monitering(philos, info);
	if (join_philosophers_thread(philos, info) == FAILUER)
		return (FAILUER);
	return (SUCCESS);
}

/*
	main_threadでやること

	全スレッドを呼び出して、そのスレッドが終了するのをpthread_joinで待機する。
	リソースを適切に開放する



*/
