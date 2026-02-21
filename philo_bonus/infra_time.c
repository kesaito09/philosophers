/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infra_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 19:08:42 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/15 16:15:00 by codex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "setup_contract.h"

/*
** [Layer] Infra Layer
** このファイルの責務:
** - 現在時刻(ms)の取得を共通化する
** - 条件付きsleep(停止判定を挟む待機)を提供する
** - 監視ロジックとルーティンロジックの時間基盤を統一する
*/

long	get_time_now(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (FAILURE);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	philo_usleep(t_philo *philo, long duration_ms)
{
	long	start;

	if (!philo || duration_ms <= 0)
		return ;
	start = get_time_now();
	while (!is_simulation_finished(philo))
	{
		if (get_time_now() - start >= duration_ms)
			break ;
		usleep(500);
	}
}
