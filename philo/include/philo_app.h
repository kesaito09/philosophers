/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_app.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:55:09 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/25 16:55:14 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_APP_H
# define PHILO_APP_H
# include "philo_types.h"

int		start_simulation(t_philo *philos, t_info *info);
int		monitoring(t_philo *philos, t_info *info);
void	set_simulation_stop(t_info *info);
#endif
