/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_resource_locks.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 17:22:09 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/25 17:22:26 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_infra.h"

int	infra_init_info_locks(t_info *info)
{
	info->state_lock = sync_create();
	if (!info->state_lock)
		return (FAILURE);
	info->write_lock = sync_create();
	if (!info->write_lock)
	{
		sync_destroy(info->state_lock);
		info->state_lock = NULL;
		return (FAILURE);
	}
	return (SUCCESS);
}

void	infra_destroy_info_locks(t_info *info)
{
	if (!info)
		return ;
	sync_destroy(info->state_lock);
	sync_destroy(info->write_lock);
}

int	infra_init_philo_lock(t_philo *philo)
{
	philo->last_eat_lock = sync_create();
	if (!philo->last_eat_lock)
		return (FAILURE);
	return (SUCCESS);
}

void	infra_destroy_philo_locks(t_philo *philos, int count)
{
	int	i;
	i = 0;
	while (i < count)
	{
		sync_destroy(philos[i].last_eat_lock);
		i++;
	}
}
