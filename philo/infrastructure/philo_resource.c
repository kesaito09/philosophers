/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_resource.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 17:18:29 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/25 17:35:43 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_infra.h"
#include <stdlib.h>

void	infra_destroy_forks(void **forks, int count)
{
	int	i;

	if (!forks)
		return ;
	i = 0;
	while (i < count)
	{
		sync_destroy(forks[i]);
		i++;
	}
	free(forks);
}

static int	init_forks_mutexes(void **forks, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		forks[i] = sync_create();
		if (!forks[i])
			return (infra_destroy_forks(forks, i), FAILURE);
		i++;
	}
	return (SUCCESS);
}

void	**infra_create_forks(int count)
{
	void	**forks;

	forks = ft_calloc((size_t)count, sizeof(void *));
	if (!forks)
		return (NULL);
	if (init_forks_mutexes(forks, count) == FAILURE)
		return (NULL);
	return (forks);
}
