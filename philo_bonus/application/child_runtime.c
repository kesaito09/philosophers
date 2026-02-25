#include "bonus_app.h"
#include "bonus_domain.h"
#include "bonus_infra.h"
#include <stdlib.h>
#include <unistd.h>
#define DEATH_GRACE_MS 100
bool	is_simulation_finished(t_philo *philo)
{
	bool	flag;
	if (!philo || !philo->info)
		return (true);
	if (retry_sem_wait(philo->info->state_lock) == FAILURE)
		return (true);
	flag = philo->info->is_stop_sim;
	if (sem_post(philo->info->state_lock) != 0)
		return (true);
	return (flag);
}
void	set_simulation_stop(t_info *info)
{
	if (retry_sem_wait(info->state_lock) == FAILURE)
		return ;
	info->is_stop_sim = true;
	sem_post(info->state_lock);
}
static long	get_last_eat_time(t_philo *philo)
{
	long	last_eat;
	if (!philo)
		return (0);
	if (retry_sem_wait(philo->sem_meal) == FAILURE)
		return (get_time_now());
	last_eat = philo->time_last_eat;
	if (sem_post(philo->sem_meal) != 0)
		return (get_time_now());
	return (last_eat);
}
static void	*monitor_routine(void *arg)
{
	t_philo	*philo;
	long	last_eat;
	philo = (t_philo *)arg;
	while (!is_simulation_finished(philo))
	{
		last_eat = get_last_eat_time(philo);
		if (get_time_now() - last_eat
			> philo->info->time_to_die + DEATH_GRACE_MS)
		{
			set_simulation_stop(philo->info);
			logger(philo, DIE);
			exit(EXIT_DEAD);
		}
		usleep(500);
	}
	return (NULL);
}
int	child_runtime(t_philo *philo)
{
	pthread_t	monitor;
	int			result;
	if (pthread_create(&monitor, NULL, monitor_routine, philo) != 0)
		return (FAILURE);
	if (pthread_detach(monitor) != 0)
		return (FAILURE);
	result = philo_routine(philo);
	set_simulation_stop(philo->info);
	return (result);
}
