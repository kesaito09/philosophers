/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 06:04:46 by kesaitou          #+#    #+#             */
/*   Updated: 2026/03/11 09:13:17 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_app.h"
#include "../include/philo_infra.h"
#include <sys/wait.h>

static int	parse_exit_status(int status)
{
	if (WIFSIGNALED(status) || !WIFEXITED(status))
		return (EXIT_ERROR);
	return (WEXITSTATUS(status));
}

static int	handle_child_exit(t_info *info, pid_t pid,
	int remaining, int exit_status)
{
	terminate_children(info, pid, remaining);
	if (exit_status == EXIT_DEAD)
		return (SUCCESS);
	return (FAILURE);
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
		exit_status = parse_exit_status(status);
		if (exit_status == EXIT_DONE)
		{
			i++;
			continue ;
		}
		return (handle_child_exit(info, pid,
				info->rule.num_of_philo - i - 1, exit_status));
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
