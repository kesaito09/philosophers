#include "bonus_infra.h"
#include "bonus_domain.h"
#include <errno.h>
#include <stdio.h>
static const char	*get_message(t_state state)
{
	if (state == TAKE)
		return ("has taken a fork");
	if (state == EAT)
		return ("is eating");
	if (state == SLEEP)
		return ("is sleeping");
	if (state == THINK)
		return ("is thinking");
	if (state == DIE)
		return ("died");
	return ("error");
}
static bool	is_log_allowed(t_philo *philo, t_state state)
{
	bool	allowed;
	while (sem_wait(philo->info->state_lock) == -1)
	{
		if (errno != EINTR)
			return (false);
	}
	allowed = true;
	if (philo->info->is_stop_sim && state != DIE)
		allowed = false;
	if (sem_post(philo->info->state_lock) != 0)
		return (false);
	return (allowed);
}
int	logger(t_philo *philo, t_state state)
{
	long		elapsed;
	const char	*msg;
	if (!philo || !philo->info)
		return (FAILURE);
	if (!is_log_allowed(philo, state))
		return (FAILURE);
	if (sem_wait(philo->info->write_lock) != 0)
		return (FAILURE);
	elapsed = get_time_now() - philo->info->start_time;
	msg = get_message(state);
	printf("%ld %d %s\n", elapsed, philo->id, msg);
	sem_post(philo->info->write_lock);
	return (SUCCESS);
}
