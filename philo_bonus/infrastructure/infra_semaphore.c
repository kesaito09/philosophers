#include "bonus_infra.h"
#include <errno.h>
#include <fcntl.h>
int	sem_unlink_wrapper(char *sem_name)
{
	if (sem_unlink(sem_name) == -1 && errno != ENOENT)
		return (FAILURE);
	return (SUCCESS);
}
sem_t	*sem_open_wrapper(char *sem_name, int n)
{
	sem_t	*sem;
	if (sem_unlink_wrapper(sem_name) == FAILURE)
		return (NULL);
	sem = sem_open(sem_name, O_CREAT, 0644, n);
	if (sem == SEM_FAILED)
		return (NULL);
	return (sem);
}
static void	sem_close_wrapper(sem_t *sem)
{
	if (sem)
		sem_close(sem);
}
int	cleanup_semaphores(t_info *info)
{
	if (!info)
		return (FAILURE);
	if (info->forks)
		sem_close_wrapper(info->forks);
	if (info->sem_sit)
		sem_close_wrapper(info->sem_sit);
	if (info->write_lock)
		sem_close_wrapper(info->write_lock);
	if (info->state_lock)
		sem_close_wrapper(info->state_lock);
	sem_unlink_wrapper(SEM_FORKS);
	sem_unlink_wrapper(SEM_SIT);
	sem_unlink_wrapper(SEM_WRITE);
	sem_unlink_wrapper(SEM_STATE);
	info->forks = NULL;
	info->sem_sit = NULL;
	info->write_lock = NULL;
	info->state_lock = NULL;
	return (SUCCESS);
}
