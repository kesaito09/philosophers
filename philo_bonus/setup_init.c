/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 22:43:22 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/19 15:59:22 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "setup_contract.h"

/*
** [Layer] Setup Layer
** このファイルの責務:
** - t_info / t_philo の初期化をまとめる
** - CLI引数のパースと検証を行う
** - 実行前に必要な共有状態(開始時刻・カウンタ初期値)を確定する
** - リソース確保失敗時のロールバック起点を提供する
*/

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
		value = value * 10 + (unsigned long)(s[i] - '0');
		if (value > LONG_MAX)
			return (FAILURE);
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
	info->num_of_philo = (int)value;
	return (SUCCESS);
}

static int	parse_time_values(char **av, t_info *info)
{
	if (parse_atol(av[2], &info->time_to_die) == FAILURE)
		return (FAILURE);
	if (parse_atol(av[3], &info->time_to_eat) == FAILURE)
		return (FAILURE);
	if (parse_atol(av[4], &info->time_to_sleep) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int	parse_must_eat(int ac, char **av, t_info *info)
{
	if (ac == 6)
		return (parse_atol(av[5], &info->num_must_eat));
	info->num_must_eat = UNSET_MUST_EAT;
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

static void	set_initial_meal_times(t_philo *philos, t_info *info)
{
	int	i;

	info->start_time = get_time_now();
	i = 0;
	while (i < info->num_of_philo)
	{
		philos[i].time_last_eat = info->start_time;
		i++;
	}
}

static int	init_info_resources(t_info *info)
{
	info->forks = sem_open_wrapper(SEM_FORKS, info->num_of_philo);
	if (!info->forks)
		return (FAILURE);
	info->sem_sit = sem_open_wrapper(SEM_SIT, info->num_of_philo - 1);
	if (!info->sem_sit)
		return (cleanup_semaphores(info), FAILURE);
	info->sem_stop = sem_open_wrapper(SEM_STOP, 1);
	if (!info->sem_stop)
		return (cleanup_semaphores(info), FAILURE);
	info->sem_write = sem_open_wrapper(SEM_WRITE, 1);
	if (!info->sem_write)
		return (cleanup_semaphores(info), FAILURE);
	return (SUCCESS);
}

t_info	*init_info(int ac, char **av)
{
	t_info	*info;

	info = ft_calloc(1, sizeof(t_info));
	if (!info)
		return (NULL);
	if (parse_input(ac, av, info) == FAILURE)
		return (free(info), NULL);
	if (init_info_resources(info) == FAILURE)
		return (free(info), NULL);
	info->is_stop_sim = false;
	info->start_time = 0;
	return (info);
}

static char	*get_sem_name(int id)
{
	char	*id;
	char	*sem_name;

	id = ft_itoa(id);
	if (!id)
		return (NULL);
	sem_name = ft_strjoin("sem_", id);
	free(id);
	return (sem_name);
}

static int	init_single_philo(t_philo *philo, t_info *info, int index)
{
	char	*sem_name;

	philo->id = index + 1;
	philo->eat_count = 0;
	philo->time_last_eat = 0;
	sem_name = get_sem_name(philo->id);
	if (!sem_name)
		return (FAILURE);
	philo->sem_eat = sem_open_wrapper(sem_name, 1);
	if (!philo->sem_eat)
		return (FAILURE);
	philo->info = info;
	return (SUCCESS);
}

t_philo	*init_philo(t_info *info)
{
	t_philo	*philos;
	int		i;

	philos = ft_calloc((size_t)info->num_of_philo, sizeof(t_philo));
	if (!philos)
		return (NULL);
	i = 0;
	while (i < info->num_of_philo)
	{
		if (init_single_philo(&philos[i], info, i) == FAILURE)
		{
			return (NULL);
		}
		i++;
	}
	return (philos);
}

int	initializer(int ac, char **av, t_philo **philos, t_info **info)
{
	if (!philos || !info)
		return (FAILURE);
	*info = init_info(ac, av);
	if (!*info)
		return (FAILURE);
	*philos = init_philo(*info);
	set_initial_meal_times(*philos, *info);
	return (SUCCESS);
}
