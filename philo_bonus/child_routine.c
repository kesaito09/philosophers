/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 15:55:48 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/21 21:14:45 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "setup_contract.h"

int	take_forks(t_info *info)
{
	if (sem_wait(info->sem_sit) != 0 || sem_wait(info->forks) != 0
		|| sem_wait(info->forks) != 0)
		return (FAILURE);
	return (SUCCESS);
}

int	back_forks(t_info *info)
{
	if (sem_post(info->forks) != 0
		|| sem_post(info->forks) != 0
		|| sem_post(info->sem_sit) != 0)
		return (FAILURE);
	return (SUCCESS);
}

int	philo_eat(t_philo *philo, t_info *info)
{
	if (take_forks(info) == FAILURE)
		return (FAILURE);
	philo_usleep(philo, info->time_to_eat);
	if (back_forks(info) == FAILURE)
		return (FAILURE);
}

int	philo_sleep(t_philo *philo, t_info *info)
{
	philo_usleep(philo, info->time_to_sleep);
}

int	philo_think(t_philo *philo, t_info *info)
{
}
