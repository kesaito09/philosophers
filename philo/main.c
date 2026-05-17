/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 12:00:00 by kesaitou          #+#    #+#             */
/*   Updated: 2026/05/17 14:00:00 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static int	print_error(void);

int	main(int ac, char **av)
{
	t_info	info;

	if (ac != 5 && ac != 6)
		return (print_error());
	if (init_simulation(ac, av, &info) == FAILURE)
		return (print_error());
	if (start_simulation(&info) == FAILURE)
	{
		destroy_simulation(&info);
		return (print_error());
	}
	destroy_simulation(&info);
	return (0);
}

static int	print_error(void)
{
	write(2, "Error\n", 6);
	return (1);
}
