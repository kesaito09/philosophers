/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 22:36:23 by kesaitou          #+#    #+#             */
/*   Updated: 2026/03/02 00:00:00 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_types.h"
#include <limits.h>

static int	parse_atol(const char *s, long *out)
{
	unsigned long	value;
	int				i;

	if (!s || !*s)
		return (FAILURE);
	i = 0;
	if (s[i] == '+')
		i++;
	if (!s[i])
		return (FAILURE);
	value = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (FAILURE);
		if (value > ((unsigned long)LONG_MAX - (s[i] - '0')) / 10)
			return (FAILURE);
		value = (value * 10) + (unsigned long)(s[i] - '0');
		i++;
	}
	if (value == 0)
		return (FAILURE);
	*out = (long)value;
	return (SUCCESS);
}

static int	parse_num_of_philo(const char *arg, t_info *info)
{
	long	value;

	if (parse_atol(arg, &value) == FAILURE)
		return (FAILURE);
	if (value > INT_MAX)
		return (FAILURE);
	info->rule.num_of_philo = (int)value;
	return (SUCCESS);
}

static int	parse_time_values(char **av, t_info *info)
{
	if (parse_atol(av[2], &info->rule.time_to_die) == FAILURE)
		return (FAILURE);
	if (parse_atol(av[3], &info->rule.time_to_eat) == FAILURE)
		return (FAILURE);
	if (parse_atol(av[4], &info->rule.time_to_sleep) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int	parse_must_eat(int ac, char **av, t_info *info)
{
	if (ac == 6)
		return (parse_atol(av[5], &info->rule.num_must_eat));
	info->rule.num_must_eat = UNSET_MUST_EAT;
	return (SUCCESS);
}

int	parse_input(int ac, char **av, t_info *info)
{
	if (!info || !av)
		return (FAILURE);
	if (ac != 5 && ac != 6)
		return (FAILURE);
	if (parse_num_of_philo(av[1], info) == FAILURE)
		return (FAILURE);
	if (parse_time_values(av, info) == FAILURE)
		return (FAILURE);
	if (parse_must_eat(ac, av, info) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
