/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_presentation.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 04:56:08 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/27 06:02:18 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_PRESENTATION_H
# define PHILO_PRESENTATION_H
# include "./philo_types.h"

int		parse_input(int ac, char **av, t_info *info);
int		initializer(int ac, char **av, t_philo **philos, t_info **info);
t_philo	*init_philo(t_info *info);
void	destroy_simulation(t_philo *philos, t_info *info);
void	destroy_philos_by_count(t_philo *philos, int count);
#endif
