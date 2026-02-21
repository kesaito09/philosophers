/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_runtime.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 15:49:28 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/21 19:40:52 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "setup_contract.h"

/*
** [Layer] Child Runtime Layer
** このファイルの責務:
** - 子プロセス起動直後の手順を管理する
** - 子プロセス内監視(死亡判定)を行う
** - eat/sleep/think のルーティンを実行する
** - ログ出力要求をInfra層へ渡す
*/

int	child_runtime(t_philo *philo, t_info *info)
{
	pthread_t	monitor;

	
	
}
/*
** [Section] Child Bootstrap
** - 監視とルーティンの開始順序を保証する
** - 子プロセス終了コードを統一して返す
**
** 想定する関数(実装はまだ書かない):
** - philo_child_entry(...)
** - start_child_monitor_thread(...)
** - join_or_detach_child_monitor(...)
*/

/*
** [Section] Child Monitor
** - 各哲学者の time_to_die 超過を監視する
** - 死亡検知時にログ出力と終了シグナル通知を行う
** - 必要なら must_eat 達成監視も扱う
**
** 想定する関数(実装はまだ書かない):
** - child_monitor_routine(void *arg)
** - detect_philo_death(...)
** - notify_child_termination_reason(...)
*/

/*
** [Section] Child Routine
** - eat -> sleep -> think のループ本体を実装する
** - フォーク取得/返却、食事時刻更新、eat_count更新を行う
** - stop条件を見てループを終了する
**
** 想定する関数(実装はまだ書かない):
** - run_philosopher_routine(...)
** - do_eat(...)
** - do_sleep_and_think(...)
*/


int	philo_routine(t_philo *philo, t_info *info)
{

	
	
	
}
