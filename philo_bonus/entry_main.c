/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 18:24:17 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/19 11:05:24 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "setup_contract.h"

/*
** [Layer] Entry Layer
** このファイルの責務:
** - プログラム全体の実行フローを制御する
** - 想定フロー:
**   構造体初期化 -> セマフォ初期化 -> プロセス作成 ->
**   親プロセス監視 -> 異常/終了時に全体終了処理
** - 他レイヤ(初期化/実行/監視/終了処理)の呼び出し順だけを持ち、
**   個別ロジックは持たない
*/


int main(int ac, char **av)
{
	t_info	info;
	t_philo	*philos;

	if (parse_input(ac, av, &info) == FAILURE)
		return (1);	
	
	
	
	
	
	
	
	
}







// int main(void)
// {
// 	// sem_t	*forks;
// 	sem_t	*write;
// 	int		pid[5];

// 	// sem_unlink(SEM_FORKS);
// 	sem_unlink(SEM_WRITE);
// 	// forks = sem_open(SEM_FORKS,O_CREAT, 0644, 5);
// 	write = sem_open(SEM_WRITE, O_CREAT, 0644, 1);
// 	for (int i = 0; i < 5; i++)
// 	{
// 		pid[i] = fork();
// 		if (pid[i] < 0)
// 			return (1);
// 		if (pid[i] == 0)
// 		{
// 			sem_wait(write);
// 			printf("%s%d\n","this processID = ",i);
// 			sem_post(write);
// 			exit(0);
// 		}
// 	}
// 	for (int i = 0; i < 5; i++)
// 		waitpid(pid[i], NULL, 0);
// 	return (0);
// }
