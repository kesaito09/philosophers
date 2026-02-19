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
** - セマフォ初期化を開始する
** - プロセス生成レイヤへ処理を委譲する
** - 親監視レイヤを起動し、終了条件の統括を行う
*/



int	setup_semaphore(t_info *info)
{
	info->forks = sem_open_wrapper(SEM_FORKS, info->num_of_philo);
	info->sem_sit = sem_open_wrapper(SEM_SIT, info->num_of_philo - 1);
	info->sem_stop = sem_open_wrapper(SEM_STOP, 1);
	info->sem_write = sem_open_wrapper(SEM_WRITE, 1);
	if (!info->forks || !info->sem_write || !info->sem_stop)
		return (FAILURE);
	return (SUCCESS);
}

int start_simulation(t_philo *philos, t_info *info)
{

	
	
	
	
	
}


/*
	セマフォ初期化
	プロセス作成
	



	
*/
