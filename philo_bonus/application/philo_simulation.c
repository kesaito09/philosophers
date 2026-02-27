/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 06:04:46 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/27 08:33:35 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_app.h"
#include "../include/philo_domain.h"
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static void	kill_children(t_info *info, pid_t except)
{
	int	i;

	i = 0;
	while (i < info->num_of_philo)
	{
		if (info->pids[i] > 0 && info->pids[i] != except)
			kill(info->pids[i], SIGTERM);
		i++;
	}
}

static void	reap_children(int remaining)
{
	while (remaining > 0)
	{
		waitpid(-1, NULL, 0);
		remaining--;
	}
}

static int	spawn_children(t_philo *philos, t_info *info)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < info->num_of_philo)
	{
		pid = fork();
		if (pid < 0)
			return (kill_children(info, -1), reap_children(i), FAILURE);
		if (pid == 0)
		{
			if (monitoring(&philos[i]) == SUCCESS)
				exit(EXIT_DONE);
			exit(EXIT_DEAD);
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
	while (i < info->num_of_philo)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == -1)
			return (FAILURE);
		if (WIFSIGNALED(status))
			return (kill_children(info, pid), reap_children(info->num_of_philo
					- i - 1), SUCCESS);
		if (WIFEXITED(status) && (WEXITSTATUS(status) == EXIT_DEAD
				|| WEXITSTATUS(status) == EXIT_ERROR))
			return (kill_children(info, pid), reap_children(info->num_of_philo
					- i - 1), SUCCESS);
		i++;
	}
	return (SUCCESS);
}

int	start_simulation(t_philo *philos, t_info *info)
{
	if (!philos || !info || !info->pids)
		return (FAILURE);
	if (spawn_children(philos, info) == FAILURE)
		return (FAILURE);
	if (wait_all_philos(info) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
