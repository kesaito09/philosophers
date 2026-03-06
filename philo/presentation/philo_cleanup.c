/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:39:15 by kesaitou          #+#    #+#             */
/*   Updated: 2026/03/03 22:10:52 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_infra.h"
#include "../include/philo_presentation.h"
#include <stdlib.h>

void	destroy_philos_by_count(t_philo_handler *philos, int count)
{
	if (!philos)
		return ;
	infra_destroy_philo_locks(philos, count);
	free(philos);
}

static void	destroy_info(t_info *info)
{
	if (!info)
		return ;
	infra_destroy_forks(info->forks, info->rule.num_of_philo);
	infra_destroy_info_locks(info);
	free(info);
}

void	destroy_simulation(t_philo_handler *philos, t_info *info)
{
	if (info)
		destroy_philos_by_count(philos, info->rule.num_of_philo);
	destroy_info(info);
}
