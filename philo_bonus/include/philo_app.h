/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_app.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 04:55:59 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/27 05:35:57 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_APP_H
# define PHILO_APP_H
# include "./philo_types.h"

int		start_simulation(t_philo *philos, t_info *info);
int		monitoring(t_philo *philo);
#endif
