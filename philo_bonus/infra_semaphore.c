/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infra_semaphore.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 20:20:00 by codex             #+#    #+#             */
/*   Updated: 2026/02/22 20:20:00 by codex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "setup_contract.h"

int	sem_unlink_wrapper(char *sem_name)
{
	if (sem_unlink(sem_name) == -1 && errno != ENOENT)
		return (FAILURE);
	return (SUCCESS);
}

sem_t	*sem_open_wrapper(char *sem_name, int n)
{
	sem_t	*sem;

	if (sem_unlink_wrapper(sem_name) == FAILURE)
		return (NULL);
	sem = sem_open(sem_name, O_CREAT, 0644, n);
	if (sem == SEM_FAILED)
		return (NULL);
	return (sem);
}

static void	sem_close_wrapper(sem_t *sem)
{
	if (sem)
		sem_close(sem);
}

int	cleanup_semaphores(t_info *info)
{
	if (!info)
		return (FAILURE);
	if (info->forks)
		sem_close_wrapper(info->forks);
	if (info->sem_sit)
		sem_close_wrapper(info->sem_sit);
	if (info->sem_write)
		sem_close_wrapper(info->sem_write);
	if (info->sem_state)
		sem_close_wrapper(info->sem_state);
	sem_unlink_wrapper(SEM_FORKS);
	sem_unlink_wrapper(SEM_SIT);
	sem_unlink_wrapper(SEM_WRITE);
	sem_unlink_wrapper(SEM_STATE);
	info->forks = NULL;
	info->sem_sit = NULL;
	info->sem_write = NULL;
	info->sem_state = NULL;
	return (SUCCESS);
}
