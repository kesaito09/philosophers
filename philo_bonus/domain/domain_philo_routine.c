#include "bonus_types.h"

int	domain_philo_eat(t_philo *philo);

int	domain_is_sated(t_philo *philo)
{
	int	sated;

	if (philo->info->num_must_eat == UNSET_MUST_EAT)
		return (FAILURE);
	philo->ops->lock_acquire(philo->last_eat_lock);
	sated = (philo->eat_count >= philo->info->num_must_eat);
	philo->ops->lock_release(philo->last_eat_lock);
	if (sated)
		return (SUCCESS);
	return (FAILURE);
}

static int	delay_start(t_philo *philo)
{
	if (philo->id % 2 == 0)
		return (philo->ops->sleep_ms(philo, philo->info->time_to_eat / 2));
	return (SUCCESS);
}

static int	sleep_and_think(t_philo *philo)
{
	long	think_time;

	if (philo->ops->log_action(philo, STATE_SLEEP) == FAILURE)
		return (FAILURE);
	if (philo->ops->sleep_ms(philo, philo->info->time_to_sleep) == FAILURE)
		return (FAILURE);
	if (philo->ops->log_action(philo, STATE_THINK) == FAILURE)
		return (FAILURE);
	think_time = philo->info->time_to_die
		- (philo->info->time_to_eat + philo->info->time_to_sleep);
	if (think_time > 0
		&& philo->ops->sleep_ms(philo, think_time / 2) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	domain_philo_routine(t_philo *philo)
{
	if (!philo || !philo->info || !philo->ops)
		return (FAILURE);
	if (delay_start(philo) == FAILURE)
		return (FAILURE);
	while (!philo->ops->should_stop(philo))
	{
		if (domain_philo_eat(philo) == FAILURE)
			return (FAILURE);
		if (domain_is_sated(philo) == SUCCESS)
			break ;
		if (sleep_and_think(philo) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}
