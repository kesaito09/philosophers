/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sync.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:52:00 by codex             #+#    #+#             */
/*   Updated: 2026/02/15 21:52:00 by codex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_SYNC_H
# define PHILO_SYNC_H

# include <pthread.h>

typedef pthread_mutex_t	t_lock;

int		sync_init(t_lock *lock);
void	sync_destroy(t_lock *lock);
void	sync_take(t_lock *lock);
void	sync_release(t_lock *lock);

#endif
