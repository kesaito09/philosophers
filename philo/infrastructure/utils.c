/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 19:08:42 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/15 08:08:45 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	get_time_now(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == FAILUER)
		return (FAILUER);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}



// int main(void)
// {
// 	long	time;

// 	time = get_time_now();
// 	printf("%ld\n",get_time_now() - time);
// 	usleep(5000);
// 	printf("%ld\n",get_time_now() - time);
// }


