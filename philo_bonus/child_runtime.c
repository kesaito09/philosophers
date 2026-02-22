/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_runtime.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 20:20:00 by codex             #+#    #+#             */
/*   Updated: 2026/02/22 20:20:00 by codex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "setup_contract.h"

bool	is_simulation_finished(t_philo *philo)
{
	bool	flag;

	while (sem_wait(philo->info->sem_state) == -1)
	{
		if (errno != EINTR)
			return (true);
	}
	flag = philo->info->is_stop_sim;
	if (sem_post(philo->info->sem_state) != 0)
		return (true);
	return (flag);
}

void	set_simulation_stop(t_info *info)
{
	while (sem_wait(info->sem_state) == -1)
	{
		if (errno != EINTR)
			return ;
	}
	info->is_stop_sim = true;
	sem_post(info->sem_state);
}

static long	get_last_eat_time(t_philo *philo)
{
	long	last_eat;

	while (sem_wait(philo->sem_meal) == -1)
	{
		if (errno != EINTR)
			return (get_time_now());
	}
	last_eat = philo->time_last_eat;
	if (sem_post(philo->sem_meal) != 0)
		return (get_time_now());
	return (last_eat);
}

static void	*monitor_routine(void *arg)
{
	t_philo	*philo;
	long	last_eat;

	philo = (t_philo *)arg;
	while (!is_simulation_finished(philo))
	{
		last_eat = get_last_eat_time(philo);
		if (get_time_now() - last_eat >= philo->info->time_to_die)
		{
			set_simulation_stop(philo->info);
			logger(philo, DIE);
			exit(EXIT_DEAD);
		}
		usleep(500);
	}
	return (NULL);
}

/*
 * 子プロセス側の統括関数:
 * 1) 監視スレッドを起動する
 * 2) 哲学者ルーティンを実行する
 * 3) 終了フラグを立てて終了する
 */
int	child_runtime(t_philo *philo, t_info *info)
{
	pthread_t	monitor;
	int			result;

	if (pthread_create(&monitor, NULL, monitor_routine, philo) != 0)
		return (FAILURE);
	if (pthread_detach(monitor) != 0)
		return (FAILURE);
	result = philo_routine(philo);
	set_simulation_stop(info);
	if (result == SUCCESS)
		return (SUCCESS);
	return (FAILURE);
}
