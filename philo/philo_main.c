/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 20:41:08 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/15 16:15:00 by codex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_info	*info;
	t_philo	*philos;

	if (ac != 5 && ac != 6)
		return (1);
	info = NULL;
	philos = NULL;
	if (initializer(ac, av, &philos, &info) == FAILURE)
		return (1);
	if (start_simulation(philos, info) == FAILURE)
	{
		destroy_simulation(philos, info);
		return (1);
	}
	destroy_simulation(philos, info);
	return (0);
}
