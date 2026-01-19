/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 22:56:37 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/19 08:18:19 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static char	*get_message(t_state state)
{
	if (state == TAKE)
        return ("has taken a fork");
    else if (state == EAT)
        return ("is eating");
    else if (state == SLEEP)
        return ("is sleeping");
    else if (state == THINK)
        return ("is thinking");
    else if (state == DIE)
        return ("died");
    return ("error");
}

int	print_log(t_philo *philo, t_state state)
{
	char	*msg;
	long	time;

	pthread_mutex_lock(&philo->info->write_lock);
	if (is_dead(philo->info) && state != DIE)
	{
		pthread_mutex_unlock(&philo->info->write_lock);
		return (FAILUER);
	}
	time = get_time_now() - philo->info->start_time;
	msg = get_message(state);
	printf("%ld %d %s\n",time, philo->id, msg);
	pthread_mutex_unlock(&philo->info->write_lock);
	return (SUCCESS);
}

