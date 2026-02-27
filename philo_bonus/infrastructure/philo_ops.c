#include "../include/philo_infra.h"

int		ops_log_action(t_philo *self, t_state state);
long	ops_get_time(void);
void	ops_sleep_ms(t_philo *self, long duration_ms);
int		ops_take_forks(t_philo *self);
void	ops_drop_forks(t_philo *self);
void	ops_lock_acquire(void *lock);
void	ops_lock_release(void *lock);
bool	ops_should_stop(t_philo *self);
static t_domain_ops	g_domain_ops = {
	.log_action = ops_log_action,
	.get_time = ops_get_time,
	.sleep_ms = ops_sleep_ms,
	.take_forks = ops_take_forks,
	.drop_forks = ops_drop_forks,
	.lock_acquire = ops_lock_acquire,
	.lock_release = ops_lock_release,
	.should_stop = ops_should_stop,
};
t_domain_ops	*get_domain_ops(void)
{
	return (&g_domain_ops);
}
