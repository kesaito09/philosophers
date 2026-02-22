/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_runtime.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 20:20:00 by codex             #+#    #+#             */
/*   Updated: 2026/02/22 21:42:15 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "setup_contract.h"

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
			if (child_runtime(&philos[i]) == SUCCESS)
				exit(EXIT_DONE);
			exit(EXIT_DEAD);
		}
		info->pids[i] = pid;
		i++;
	}
	return (SUCCESS);
}

static int	wait_children(t_info *info)
{
	int		finished;
	int		status;
	pid_t	pid;

	finished = 0;
	while (finished < info->num_of_philo)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == -1)
			return (FAILURE);
		if (WIFSIGNALED(status))
			return (kill_children(info, pid),
				reap_children(info->num_of_philo - finished - 1), SUCCESS);
		if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_DEAD)
			return (kill_children(info, pid),
				reap_children(info->num_of_philo - finished - 1), SUCCESS);
		finished++;
	}
	return (SUCCESS);
}

/*
 * 親プロセス側の統括関数:
 * 1) 子プロセスを生成する
 * 2) 子プロセス終了を監視し、必要時に全体停止する
 */
int	start_simulation(t_philo *philos, t_info *info)
{
	if (!philos || !info || !info->pids)
		return (FAILURE);
	if (spawn_children(philos, info) == FAILURE)
		return (FAILURE);
	if (wait_children(info) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
