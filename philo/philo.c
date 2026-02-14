/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 20:41:08 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/14 15:45:31 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"




int main(int ac, char **av)
{
    t_info	*info;
	t_philo	*philo;

	if (ac != 5 && ac != 6)
		return (1);
	info = init_info(ac, av);
	if (!info)
		return (1);
	philo = init_philo(info);
    if (!philo)
		return (1);
	info->start_time = get_time_now();
    
    
    
}


/*
	int main()
	{
		setup();
		simulate()
		destroy()
	}
*/

