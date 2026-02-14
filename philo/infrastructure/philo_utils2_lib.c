/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2_lib.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 19:08:42 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/15 02:11:30 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*死亡フラグを確認しにいく関数*/
bool is_dead(t_philo *philo)
{
	bool	flag;

	pthread_mutex_lock(&philo->info.dead_flag);
	flag = philo->info.is_dead;
	pthread_mutex_unlock(&philo->info.dead_flag);
	return (flag);
}

long	get_time_now(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == FAILUER)
		return (FAILUER);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int main(void)
{
	long	time;

	time = get_time_now();
	printf("%ld\n",get_time_now() - time);
	usleep(5000);
	printf("%ld\n",get_time_now() - time);
}


