/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_app.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:55:09 by kesaitou          #+#    #+#             */
/*   Updated: 2026/03/02 17:54:07 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_APP_H
# define PHILO_APP_H
# include "./philo_types.h"

void	*philo_routine(void *arg);
int		start_simulation(t_philo_handler *philos, t_info *info);
int		monitoring(t_philo_handler *philos);

#endif
