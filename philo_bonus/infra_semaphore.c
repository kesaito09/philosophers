/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infra_semaphore.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 14:45:32 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/19 15:22:03 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "setup_contract.h"

/*
** [Layer] Infra Layer
** このファイルの責務:
** - sem_open / sem_close / sem_unlink のラッパーを提供する
** - エラーハンドリングを集約し、上位層を簡潔に保つ
** - 名前付きセマフォのライフサイクルを一箇所で扱う
** - セマフォを中心とした共通cleanup責務の窓口を持つ
*/

/*
** [Section] Cleanup Policy
** - 親側で保持するセマフォを close/unlink する
** - 異常系を含む終了経路で後始末を共通化する
** - 二重close/二重unlinkを防ぐ終端ポリシーを管理する
**
** 想定する関数(実装はまだ書かない):
** - cleanup_semaphores(...)
*/

int	sem_unlink_wrapper(sem_t *sem)
{
	if (sem_unlink(sem) == -1 && errno != ENOENT)
	{
		perror("unlink failed");
		return (FAILURE);
	}	
	return (SUCCESS);
}

sem_t	*sem_open_wrapper(char *sem_name, int n)
{
	sem_t	*sem;

	if (sem_unlink_wrapper(sem_name) == FAILURE)
		return (NULL);
	sem = sem_open(sem_name, O_CREAT, 0644, n);
	if (sem == SEM_FAILED)
	{
		perror("sem_open critical error");
		return (NULL);
	}
	return (sem);
}

void	sem_close_wrapper(sem_t *sem)
{
	if (sem_close(sem) == SEM_FAILED)
		perror("sem_close failed");
}

int	cleanup_semaphores(t_info *info)
{
	if (!info)
		return (FAILURE);	
	if (info->forks)
	{
		sem_close_wrapper(info->forks);
		sem_unlink_wrapper(info->forks);
	}	
	if (info->sem_sit)
	{
		sem_close_wrapper(info->sem_sit);
		sem_unlink_wrapper(info->sem_sit);
	}
	if (info->sem_stop)
	{
		sem_close_wrapper(info->sem_stop);
		sem_unlink_wrapper(info->sem_stop);
	}
	if (info->sem_write)
	{
		sem_close_wrapper(info->sem_write);
		sem_unlink_wrapper(info->sem_write);
	}
	return (SUCCESS);
}










