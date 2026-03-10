/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 06:04:46 by kesaitou          #+#    #+#             */
/*   Updated: 2026/03/10 01:47:56 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_app.h"
#include "../include/philo_infra.h"
#include <sys/wait.h>

static int	handle_wait_status(int status)
{
	if (WIFSIGNALED(status))
		return (EXIT_ERROR);
	if (!WIFEXITED(status))
		return (EXIT_ERROR);
	return (WEXITSTATUS(status));
}

static int	wait_all_philos(t_info *info)
{
	int		i;
	int		status;
	int		exit_status;
	pid_t	pid;

	i = 0;
	while (i < info->rule.num_of_philo)
	{
		pid = retry_waitpid(&status);
		if (pid == -1)
			return (FAILURE);
		exit_status = handle_wait_status(status);
		if (exit_status == EXIT_DONE)
		{
			i++;
			continue ;
		}
		terminate_children(info, pid, info->rule.num_of_philo - i - 1);
		if (exit_status == EXIT_DEAD)
			return (SUCCESS);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	start_simulation(t_philo_handler *philos, t_info *info)
{
	if (!philos || !info || !info->pids)
		return (FAILURE);
	if (spawn_children(philos, info) == FAILURE)
		return (FAILURE);
	if (wait_all_philos(info) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
