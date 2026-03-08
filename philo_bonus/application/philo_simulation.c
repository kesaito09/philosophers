/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 06:04:46 by kesaitou          #+#    #+#             */
/*   Updated: 2026/03/06 00:00:00 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_app.h"
#include "../include/philo_infra.h"
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static void	terminate_children(t_info *info, pid_t except, int remaining)
{
	int	i;

	i = 0;
	while (i < info->rule.num_of_philo)
	{
		if (info->pids[i] > 0 && info->pids[i] != except)
			kill(info->pids[i], SIGTERM);
		i++;
	}
	while (remaining > 0)
	{
		waitpid(-1, NULL, 0);
		remaining--;
	}
}

static int	handle_wait_status(t_info *info, int status, pid_t pid, int index)
{
	if (WIFSIGNALED(status))
		return (terminate_children(info, pid,
				info->rule.num_of_philo - index - 1), FAILURE);
	if (!WIFEXITED(status))
		return (terminate_children(info, pid,
				info->rule.num_of_philo - index - 1), FAILURE);
	if (WEXITSTATUS(status) == EXIT_DONE)
		return (SUCCESS);
	if (WEXITSTATUS(status) == EXIT_DEAD)
		return (terminate_children(info, pid,
				info->rule.num_of_philo - index - 1), SUCCESS);
	return (terminate_children(info, pid,
			info->rule.num_of_philo - index - 1), FAILURE);
}

static int	spawn_children(t_philo_handler *philos, t_info *info)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < info->rule.num_of_philo)
	{
		pid = fork();
		if (pid < 0)
			return (terminate_children(info, -1, i), FAILURE);
		if (pid == 0)
		{
			if (run_philo_process(&philos[i]) == SUCCESS)
				exit(EXIT_DONE);
			exit(EXIT_ERROR);
		}
		info->pids[i] = pid;
		i++;
	}
	return (SUCCESS);
}

static int	wait_all_philos(t_info *info)
{
	int		i;
	int		status;
	pid_t	pid;

	i = 0;
	while (i < info->rule.num_of_philo)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == -1)
			return (FAILURE);
		if (handle_wait_status(info, status, pid, i) != SUCCESS)
			return (FAILURE);
		if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_DEAD)
			return (SUCCESS);
		i++;
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
