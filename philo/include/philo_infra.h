/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_infra.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:54:29 by kesaitou          #+#    #+#             */
/*   Updated: 2026/03/02 18:09:43 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_INFRA_H
# define PHILO_INFRA_H
# include "./philo_types.h"
# include <stddef.h>

void			*sync_create(void);

void			sync_destroy(void *lock);
void			sync_take(void *lock);
void			sync_release(void *lock);

void			set_simulation_stop(t_info *info);
long			get_time_now(void);
int				philo_usleep(t_philo *philo, long duration_ms);
bool			is_simulation_finished(t_philo *philo);
int				logger(t_philo *philo, t_state state);
long			ops_get_last_meal_ms(t_philo *self);

void			**infra_create_forks(int count);
void			infra_destroy_forks(void **forks, int count);
int				infra_init_info_locks(t_info *info);
void			infra_destroy_info_locks(t_info *info);
int				infra_init_philo_lock(t_philo_handler *handler);
void			infra_destroy_philo_locks(t_philo_handler *philos, int count);

t_domain_ops	*get_domain_ops(void);
void			*ft_calloc(size_t nmemb, size_t size);

#endif
