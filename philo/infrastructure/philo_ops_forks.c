/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_ops_forks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 17:15:56 by kesaitou          #+#    #+#             */
/*   Updated: 2026/03/03 12:32:25 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_infra.h"

static void	*first_fork(t_philo_handler *handler)
{
	if (handler->philo.id % 2 == 1)
		return (handler->right_fork);
	return (handler->left_fork);
}

static void	*second_fork(t_philo_handler *handler)
{
	if (handler->philo.id % 2 == 1)
		return (handler->left_fork);
	return (handler->right_fork);
}

static int	take_fork_single_philo(t_philo_handler *handler)
{
	sync_take(handler->left_fork);
	if (logger(&handler->philo, STATE_TAKE_FORK) == FAILURE)
	{
		sync_release(handler->left_fork);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	ops_take_fork(t_philo *self)
{
	t_philo_handler	*handler;

	if (!self)
		return (FAILURE);
	handler = (t_philo_handler *)self;
	if (self->rule->num_of_philo == 1)
		return (take_fork_single_philo(handler));
	sync_take(first_fork(handler));
	if (logger(self, STATE_TAKE_FORK) == FAILURE)
	{
		sync_release(first_fork(handler));
		return (FAILURE);
	}
	sync_take(second_fork(handler));
	if (logger(self, STATE_TAKE_FORK) == FAILURE)
	{
		sync_release(second_fork(handler));
		sync_release(first_fork(handler));
		return (FAILURE);
	}
	return (SUCCESS);
}

void	ops_drop_forks(t_philo *self)
{
	t_philo_handler	*handler;

	if (!self)
		return ;
	handler = (t_philo_handler *)self;
	if (self->rule->num_of_philo == 1)
	{
		sync_release(handler->left_fork);
		return ;
	}
	sync_release(second_fork(handler));
	sync_release(first_fork(handler));
}
