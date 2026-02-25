/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:41:56 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/25 16:41:58 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_domain.h"
#include "philo_types.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	philo = (t_philo *)arg;
	domain_philo_routine(philo);
	return (NULL);
}
