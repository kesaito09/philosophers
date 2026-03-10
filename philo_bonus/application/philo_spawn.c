/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_spawn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 02:35:00 by kesaitou          #+#    #+#             */
/*   Updated: 2026/03/10 02:35:00 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_app.h"
#include "../include/philo_infra.h"
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

pid_t	retry_waitpid(int *status)
{
	pid_t	pid;

	while (1)
	{
		pid = waitpid(-1, status, 0);
		if (pid != -1)
			return (pid);
		if (errno != EINTR)
			return (-1);
	}
}

void	terminate_children(t_info *info, pid_t except, int remaining)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < info->rule.num_of_philo)
	{
		if (info->pids[i] > 0 && info->pids[i] != except)
			kill(info->pids[i], SIGTERM);
		i++;
	}
	while (remaining > 0)
	{
		pid = retry_waitpid(NULL);
		if (pid == -1)
			break ;
		if (pid > 0)
			remaining--;
	}
}

int	spawn_children(t_philo_handler *philos, t_info *info)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < info->rule.num_of_philo)
	{
		pid = fork();
		if (pid < 0)
		{
			terminate_children(info, -1, i);
			return (FAILURE);
		}
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
