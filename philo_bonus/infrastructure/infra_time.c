#include "bonus_infra.h"
#include "bonus_app.h"
#include <sys/time.h>
#include <unistd.h>
long	get_time_now(void)
{
	struct timeval	time;
	if (gettimeofday(&time, NULL) == -1)
		return (FAILURE);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
int	philo_usleep(t_philo *philo, long duration_ms)
{
	long	start;
	if (!philo || duration_ms <= 0)
		return (SUCCESS);
	start = get_time_now();
	while (!is_simulation_finished(philo))
	{
		if (get_time_now() - start >= duration_ms)
			break ;
		usleep(500);
	}
	return (SUCCESS);
}
