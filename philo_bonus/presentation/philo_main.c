/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 05:45:01 by kesaitou          #+#    #+#             */
/*   Updated: 2026/03/06 00:00:00 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_app.h"
#include "../include/philo_presentation.h"
#include <unistd.h>

int	main(int ac, char **av)
{
	t_info			*info;
	t_philo_handler	*philos;

	info = NULL;
	philos = NULL;
	if (ac != 5 && ac != 6)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	if (initializer(ac, av, &philos, &info) == FAILURE)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	if (start_simulation(philos, info) == FAILURE)
	{
		write(2, "Error\n", 6);
		destroy_simulation(philos, info);
		return (1);
	}
	destroy_simulation(philos, info);
	return (0);
}
