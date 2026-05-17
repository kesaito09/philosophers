/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 12:00:00 by kesaitou          #+#    #+#             */
/*   Updated: 2026/05/17 14:00:00 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

static int	parse_atol(const char *s, long *out);
static int	parse_num_of_philo(const char *arg, t_rule *rule);
static int	parse_time_values(char **av, t_rule *rule);
static int	parse_must_eat(int ac, char **av, t_rule *rule);

int	parse_input(int ac, char **av, t_rule *rule)
{
	if (!rule || !av)
		return (FAILURE);
	if (parse_num_of_philo(av[1], rule) == FAILURE)
		return (FAILURE);
	if (parse_time_values(av, rule) == FAILURE)
		return (FAILURE);
	if (parse_must_eat(ac, av, rule) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

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
	*out = (long)value;
	return (SUCCESS);
}

static int	parse_num_of_philo(const char *arg, t_rule *rule)
{
	long	value;

	if (parse_atol(arg, &value) == FAILURE)
		return (FAILURE);
	if (value <= 0 || value > INT_MAX)
		return (FAILURE);
	rule->num_of_philo = (int)value;
	return (SUCCESS);
}

static int	parse_time_values(char **av, t_rule *rule)
{
	if (parse_atol(av[2], &rule->time_to_die) == FAILURE)
		return (FAILURE);
	if (parse_atol(av[3], &rule->time_to_eat) == FAILURE)
		return (FAILURE);
	if (parse_atol(av[4], &rule->time_to_sleep) == FAILURE)
		return (FAILURE);
	if (rule->time_to_die <= 0 || rule->time_to_eat <= 0
		|| rule->time_to_sleep <= 0)
		return (FAILURE);
	return (SUCCESS);
}

static int	parse_must_eat(int ac, char **av, t_rule *rule)
{
	if (ac != 6)
	{
		rule->num_must_eat = UNSET_MUST_EAT;
		return (SUCCESS);
	}
	if (parse_atol(av[5], &rule->num_must_eat) == FAILURE)
		return (FAILURE);
	if (rule->num_must_eat <= 0)
		return (FAILURE);
	return (SUCCESS);
}
