/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infra_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 20:20:00 by codex             #+#    #+#             */
/*   Updated: 2026/02/22 20:20:00 by codex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "setup_contract.h"

long	get_time_now(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (FAILURE);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

/*
 * シミュレーション終了フラグを監視しながら待機する。
 * duration_ms 到達または終了フラグ検知で戻る。
 */
int	philo_usleep(t_philo *philo, long duration_ms)
{
	long	start;

	if (!philo || duration_ms <= 0)
		return (SUCCESS);
	start = get_time_now();
	while (!is_simulation_finished(philo))
	{
		if (get_time_now() - start >= duration_ms)
			break ;
		usleep(500);
	}
	return (SUCCESS);
}
