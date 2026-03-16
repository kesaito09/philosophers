/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   domain_philo_timing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 00:00:00 by kesaitou          #+#    #+#             */
/*   Updated: 2026/03/15 00:00:00 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_domain.h"

static long	get_ideal_cycle(t_philo *philo)
{
	long	num;
	long	eat;

	num = philo->rule->num_of_philo;
	eat = philo->rule->time_to_eat;
	if (num % 2 == 0)
		return (eat * 2);
	return ((eat * num) / (num / 2));
}

static long	get_min_ready_time(t_philo *philo, long last_meal)
{
	return (last_meal + philo->rule->time_to_eat
		+ philo->rule->time_to_sleep);
}

static long	get_safety_limit(t_philo *philo, long last_meal)
{
	return (last_meal + philo->rule->time_to_die - 10);
}

static long	calculate_precession_target(t_philo *philo, long last_meal)
{
	long	target;
	long	min_ready;

	target = last_meal + get_ideal_cycle(philo);
	min_ready = get_min_ready_time(philo, last_meal);
	if (target < min_ready)
		target = min_ready;
	if (target > get_safety_limit(philo, last_meal))
		target = get_safety_limit(philo, last_meal);
	return (target);
}

int	domain_philo_think(t_philo *philo)
{
	long	last_meal;
	long	now;
	long	target_time;
	long	wait_time;

	if (philo->ops->log_action(philo, STATE_THINK) == FAILURE)
		return (FAILURE);
	last_meal = philo->ops->last_meal_ms(philo);
	if (last_meal == FAILURE)
		return (FAILURE);
	now = philo->ops->now_ms();
	if (now == FAILURE)
		return (FAILURE);
	target_time = calculate_precession_target(philo, last_meal);
	if (target_time <= now)
		return (SUCCESS);
	wait_time = target_time - now;
	if (philo->ops->sleep_ms(philo, wait_time) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
