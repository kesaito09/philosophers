/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_logger.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 22:56:37 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/15 16:15:00 by codex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "setup_contract.h"

/*
** [Layer] Child Runtime Layer
** このファイルの責務:
** - 哲学者状態(TAKE/EAT/SLEEP/THINK/DIE)の表示規約を管理する
** - 表示時刻(開始からの経過ms)の整形責務を持つ
** - 出力同期(sem_write)は呼び出し側との責務分担で運用する
*/

static const char	*get_message(t_state state)
{
	if (state == TAKE)
		return ("has taken a fork");
	if (state == EAT)
		return ("is eating");
	if (state == SLEEP)
		return ("is sleeping");
	if (state == THINK)
		return ("is thinking");
	if (state == DIE)
		return ("died");
	return ("error");
}

static void	print_state_log(t_philo *philo, t_state state)
{
	long			elapsed;
	const char		*msg;

	elapsed = get_time_now() - philo->info->start_time;
	msg = get_message(state);
	printf("%ld %d %s\n", elapsed, philo->id, msg);
}

// int	logger(t_philo *philo, t_state state)
// {
	
// }
