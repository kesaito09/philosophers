/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 12:00:00 by kesaitou          #+#    #+#             */
/*   Updated: 2026/05/21 22:21:58 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	initial_delay_ms(int id, int n, long eat);
static bool	is_sated(t_philo *philo);
static int	philo_eat(t_philo *philo);
static int	philo_think(t_philo *philo);

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	long	delay;

	philo = (t_philo *)arg;
	delay = initial_delay_ms(philo->id, philo->info->rule.num_of_philo,
			philo->info->rule.time_to_eat);
	philo_usleep(philo, delay);
	while (!is_stopped(philo->info))
	{
		if (philo_eat(philo) != SUCCESS)
			break ;
		if (is_sated(philo))
			break ;
		if (log_action(philo, STATE_SLEEP) != SUCCESS)
			break ;
		if (philo_usleep(philo, philo->info->rule.time_to_sleep) != SUCCESS)
			break ;
		if (philo_think(philo) != SUCCESS)
			break ;
	}
	return (NULL);
}

static long	initial_delay_ms(int id, int n, long eat)
{
	int	group;

	if (n == 1)
		return (0);
	if (id == n && n % 2 == 1)
		group = 2;
	else if (id % 2 == 1)
		group = 0;
	else
		group = 1;
	return ((long)group * eat);
}

static bool	is_sated(t_philo *philo)
{
	bool	sated;

	if (philo->info->rule.num_must_eat == UNSET_MUST_EAT)
		return (false);
	if (safe_lock(&philo->meal.lock) != SUCCESS)
		return (true);
	sated = (philo->meal.count >= philo->info->rule.num_must_eat);
	safe_unlock(&philo->meal.lock);
	return (sated);
}

static int	philo_eat(t_philo *philo)
{
	int	status;

	status = take_forks(philo);
	if (status != SUCCESS)
		return (status);
	if (safe_lock(&philo->meal.lock) != SUCCESS)
		return (drop_forks(philo), FAILURE);
	philo->meal.last_time = get_time_ms();
	philo->meal.count++;
	safe_unlock(&philo->meal.lock);
	status = log_action(philo, STATE_EAT);
	if (status == SUCCESS)
		status = philo_usleep(philo, philo->info->rule.time_to_eat);
	drop_forks(philo);
	return (status);
}

static int	philo_think(t_philo *philo)
{
	long	last_meal;
	long	target;
	long	wait;
	int		status;
	int		n;

	status = log_action(philo, STATE_THINK);
	if (status != SUCCESS)
		return (status);
	if (safe_lock(&philo->meal.lock) != SUCCESS)
		return (FAILURE);
	last_meal = philo->meal.last_time;
	safe_unlock(&philo->meal.lock);
	if (philo->info->rule.num_of_philo % 2 == 0)
		n = 2;
	else
		n = 3;
	target = last_meal + n * philo->info->rule.time_to_eat;
	wait = target - get_time_ms();
	if (wait <= 0)
		return (SUCCESS);
	return (philo_usleep(philo, wait));
}
