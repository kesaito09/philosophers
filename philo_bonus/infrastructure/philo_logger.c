#include "../include/philo_infra.h"
#include "../include/philo_domain.h"
#include <errno.h>
#include <stdio.h>
static const char	*get_message(t_state state)
{
	if (state == STATE_TAKE_FORK)
		return ("has taken a fork");
	if (state == STATE_EAT)
		return ("is eating");
	if (state == STATE_SLEEP)
		return ("is sleeping");
	if (state == STATE_THINK)
		return ("is thinking");
	if (state == STATE_DIE)
		return ("died");
	return ("error");
}

static bool	is_log_allowed(t_philo *philo, t_state state)
{
	bool	allowed;

	if (retry_sem_wait(philo->info->state_lock) == FAILURE)
		return (false);
	allowed = true;
	if (philo->info->is_stop_sim && state != STATE_DIE)
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
	if (retry_sem_wait(philo->info->write_lock) == FAILURE)
		return (FAILURE);
	elapsed = get_time_now() - philo->info->start_time;
	msg = get_message(state);
	printf("%ld %d %s\n", elapsed, philo->id, msg);
	sem_post(philo->info->write_lock);
	return (SUCCESS);
}
