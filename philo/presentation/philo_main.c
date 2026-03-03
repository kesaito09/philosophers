/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:39:34 by kesaitou          #+#    #+#             */
/*   Updated: 2026/03/02 17:54:07 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_app.h"
#include "../include/philo_presentation.h"

int	main(int ac, char **av)
{
	t_info		*info;
	t_philo_handler	*philos;

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
