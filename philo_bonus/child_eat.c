/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 20:20:00 by codex             #+#    #+#             */
/*   Updated: 2026/02/22 20:20:00 by codex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "setup_contract.h"

static int	retry_sem_wait(sem_t *sem)
{
	while (sem_wait(sem) == -1)
	{
		if (errno != EINTR)
			return (FAILURE);
	}
	return (SUCCESS);
}

static int	release_forks(t_info *info)
{
	if (sem_post(info->forks) != 0)
		return (FAILURE);
	if (sem_post(info->forks) != 0)
		return (FAILURE);
	if (sem_post(info->sem_sit) != 0)
		return (FAILURE);
	return (SUCCESS);
}

static int	take_forks(t_philo *philo)
{
	t_info	*info;

	info = philo->info;
	if (retry_sem_wait(info->sem_sit) == FAILURE)
		return (FAILURE);
	if (retry_sem_wait(info->forks) == FAILURE)
		return (sem_post(info->sem_sit), FAILURE);
	if (logger(philo, TAKE) == FAILURE)
		return (sem_post(info->forks), sem_post(info->sem_sit), FAILURE);
	if (retry_sem_wait(info->forks) == FAILURE)
		return (sem_post(info->forks), sem_post(info->sem_sit), FAILURE);
	if (logger(philo, TAKE) == FAILURE)
		return (release_forks(info), FAILURE);
	return (SUCCESS);
}

static int	wait_single_philo_death(t_philo *philo)
{
	if (retry_sem_wait(philo->info->forks) == FAILURE)
		return (FAILURE);
	logger(philo, TAKE);
	while (!is_simulation_finished(philo))
		philo_usleep(philo, 1);
	sem_post(philo->info->forks);
	return (FAILURE);
}

int	philo_eat(t_philo *philo)
{
	if (philo->info->num_of_philo == 1)
		return (wait_single_philo_death(philo));
	if (take_forks(philo) == FAILURE)
		return (FAILURE);
	if (retry_sem_wait(philo->sem_meal) == FAILURE)
		return (release_forks(philo->info), FAILURE);
	philo->time_last_eat = get_time_now();
	philo->eat_count++;
	if (sem_post(philo->sem_meal) != 0)
		return (release_forks(philo->info), FAILURE);
	if (logger(philo, EAT) == FAILURE)
		return (release_forks(philo->info), FAILURE);
	philo_usleep(philo, philo->info->time_to_eat);
	if (release_forks(philo->info) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
