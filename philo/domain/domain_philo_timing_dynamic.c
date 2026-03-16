/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   domain_philo_timing_dynamic.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 00:00:00 by kesaitou          #+#    #+#             */
/*   Updated: 2026/03/16 14:44:58 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_domain.h"

long	domain_get_odd_start_delay(t_philo *philo)
{
	long	num;
	long	eat;

	num = philo->rule->num_of_philo;
	eat = philo->rule->time_to_eat;
	if (num <= 1)
		return (0);
	return (((philo->id - 1) * eat) / (num / 2));
}
