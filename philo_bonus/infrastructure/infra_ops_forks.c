#include "bonus_infra.h"

int	retry_sem_wait(sem_t *sem);
int	ops_take_forks(t_philo *self, void **first, void **second)
{
	if (!self || !first || !second)
		return (FAILURE);
	*first = self->left_fork;
	*second = self->right_fork;
	if (retry_sem_wait(self->info->sem_sit) == FAILURE)
		return (FAILURE);
	if (retry_sem_wait(self->info->forks) == FAILURE)
		return (sem_post(self->info->sem_sit), FAILURE);
	if (retry_sem_wait(self->info->forks) == FAILURE)
		return (sem_post(self->info->forks), sem_post(self->info->sem_sit),
			FAILURE);
	return (SUCCESS);
}
void	ops_drop_forks(t_philo *self, void *first, void *second)
{
	(void)first;
	(void)second;
	sem_post(self->info->forks);
	sem_post(self->info->forks);
	sem_post(self->info->sem_sit);
}
