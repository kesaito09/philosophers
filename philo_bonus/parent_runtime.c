/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_runtime.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 22:42:22 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/19 15:55:44 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "setup_contract.h"

/*
** [Layer] Parent Runtime Layer
** このファイルの責務:
** - プロセス生成レイヤへ処理を委譲する
** - 親監視レイヤを起動し、終了条件の統括を行う
** - 子プロセスの生成失敗時ロールバックを行う
** - 死亡検知時に全子プロセスを停止する
*/

/*
	プロセスを生成して、
	各、プロセスはルーティンを実施する。
	ルーティンを実施する際に、テーブルに座り（セマフォ）、
	フォークを取得してルーティンを実施する。
	そのプロセス内にスレッドで監視者を実装する
	


	
	
	
	
	
	
	
	
*/


int start_simulation(t_philo *philos, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philo)
	{
		info->pids[i] = fork();
		if (info->pids[i] < 0)
			return (FAILURE);
		if (info->pids[i] == 0)
		{
			child_runtime(&philos[i], info);
		}
		
		i++;
	}
	//waitpid
	//kill=all=process
	
	
	
	
	
}

/*
** [Section] Process Control
** - 哲学者ごとの子プロセスを fork で生成する
** - 子プロセス開始点(child側エントリ)へ遷移させる
** - 生成途中で失敗した場合に既存子プロセスを停止する
** - 生成した pid 一覧を親監視処理へ引き渡す
**
** 想定する関数(実装はまだ書かない):
** - spawn_philosopher_processes(...)
** - run_child_process(...)
** - rollback_spawned_processes(...)
*/

/*
** [Section] Parent Monitoring
** - waitpid で子プロセスの終了理由を監視する
** - 「誰かが死亡した」などの終了条件を判定する
** - 条件成立時に全子プロセスへ kill を送る
** - 最終的な終了ステータスを entry 層へ返す
**
** 想定する関数(実装はまだ書かない):
** - monitor_children_and_shutdown(...)
** - handle_child_exit_status(...)
** - kill_all_children(...)
*/
