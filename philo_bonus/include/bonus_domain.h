#ifndef BONUS_DOMAIN_H
# define BONUS_DOMAIN_H

# include <stdbool.h>

typedef struct s_philo			t_philo;
typedef struct s_domain_ops	t_domain_ops;

typedef enum e_state
{
	STATE_TAKE_FORK,
	STATE_EAT,
	STATE_SLEEP,
	STATE_THINK,
	STATE_DIE,
}t_state;

struct s_domain_ops
{
	int		(*log_action)(t_philo *self, t_state state);
	long	(*get_time)(void);
	int		(*sleep_ms)(t_philo *self, long duration_ms);
	int		(*take_forks)(t_philo *self, void **first, void **second);
	void	(*drop_forks)(t_philo *self, void *first, void *second);
	void	(*lock_acquire)(void *lock);
	void	(*lock_release)(void *lock);
	int		(*should_stop)(t_philo *self);
};

# define SINGLE_PHILO_COUNT 1
# define TAKE STATE_TAKE_FORK
# define EAT STATE_EAT
# define SLEEP STATE_SLEEP
# define THINK STATE_THINK
# define DIE STATE_DIE

int		philo_routine(t_philo *philo);
int		domain_philo_routine(t_philo *philo);

#endif
