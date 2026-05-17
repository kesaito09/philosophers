/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 12:00:00 by kesaitou          #+#    #+#             */
/*   Updated: 2026/05/17 18:00:00 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static const char	*const	g_messages[] = {
	"has taken a fork",
	"is eating",
	"is sleeping",
	"is thinking",
	"died"
};

static int	put_long(long n, char *buf);
static int	format_log_msg(char *buf, long elapsed, int id, t_state state);

int	log_action(t_philo *philo, t_state state)
{
	char	buf[64];
	int		len;
	long	elapsed;
	bool	stopped;

	if (!philo || !philo->info)
		return (FAILURE);
	elapsed = get_time_ms() - philo->info->sim.start_time;
	len = format_log_msg(buf, elapsed, philo->id, state);
	pthread_mutex_lock(&philo->info->sim.write_lock);
	pthread_mutex_lock(&philo->info->sim.state_lock);
	stopped = philo->info->sim.is_stopped;
	pthread_mutex_unlock(&philo->info->sim.state_lock);
	if (stopped && state != STATE_DIE)
		return (pthread_mutex_unlock(&philo->info->sim.write_lock), STOPPED);
	write(1, buf, len);
	pthread_mutex_unlock(&philo->info->sim.write_lock);
	return (SUCCESS);
}

static int	put_long(long n, char *buf)
{
	char	tmp[24];
	int		i;
	int		len;

	if (n == 0)
	{
		buf[0] = '0';
		return (1);
	}
	i = 0;
	while (n > 0)
	{
		tmp[i++] = '0' + (n % 10);
		n /= 10;
	}
	len = i;
	while (i > 0)
		*buf++ = tmp[--i];
	return (len);
}

static int	format_log_msg(char *buf, long elapsed, int id, t_state state)
{
	int	len;
	int	i;

	len = put_long(elapsed, buf);
	buf[len++] = ' ';
	len += put_long((long)id, buf + len);
	buf[len++] = ' ';
	i = 0;
	while (g_messages[state][i])
		buf[len++] = g_messages[state][i++];
	buf[len++] = '\n';
	return (len);
}
