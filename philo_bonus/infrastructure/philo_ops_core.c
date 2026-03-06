/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_ops_core.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 08:21:03 by kesaitou          #+#    #+#             */
/*   Updated: 2026/03/03 22:34:25 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_infra.h"
#include <errno.h>

int	retry_sem_wait(sem_t *sem)
{
	while (sem_wait(sem) == -1)
	{
		if (errno != EINTR)
			return (FAILURE);
	}
	return (SUCCESS);
}
