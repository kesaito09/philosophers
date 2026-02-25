#include "bonus_infra.h"
#include "bonus_app.h"

int	retry_sem_wait(sem_t *sem);
void	ops_lock_acquire(void *lock)
{
	if (!lock)
		return ;
	retry_sem_wait((sem_t *)lock);
}
void	ops_lock_release(void *lock)
{
	if (!lock)
		return ;
	sem_post((sem_t *)lock);
}
int	ops_should_stop(t_philo *self)
{
	return (is_simulation_finished(self));
}
