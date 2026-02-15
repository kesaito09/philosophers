/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 20:41:08 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/15 08:01:40 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int main(int ac, char **av)
{
    t_info	info;
	t_philo	*philos;

	if (ac != 5 && ac != 6)
		return (1);
	philos = NULL;
	if (initializer(ac, av, philos, &info) == FAILUER)
		return (1);
    if (start_simulation(philos, &info) == FAILUER)
		return (1);
	return (0);
}


/*
	int main()
	{
		setup();
		simulate()
		destroy()
	}
*/

