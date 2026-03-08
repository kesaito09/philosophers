/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_app.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 04:55:59 by kesaitou          #+#    #+#             */
/*   Updated: 2026/03/06 00:00:00 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_APP_H
# define PHILO_APP_H
# include "./philo_types.h"

int		start_simulation(t_philo_handler *philos, t_info *info);
int		start_monitor_thread(t_philo_handler *handler);
int		run_philo_process(t_philo_handler *handler);

#endif
