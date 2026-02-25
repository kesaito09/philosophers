#ifndef BONUS_TYPES_H
# define BONUS_TYPES_H
# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include "bonus_domain.h"
# define SUCCESS 1
# define FAILURE -1
# define UNSET_MUST_EAT -1
# define EXIT_DONE 0
# define EXIT_DEAD 1
# define SEM_FORKS "/forks"
# define SEM_SIT "/sit"
# define SEM_WRITE "/write"
# define SEM_STATE "/state"
# define SEM_MEAL_PREFIX "/meal_"
typedef struct s_info
{
	pid_t			*pids;
	int				num_of_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			num_must_eat;
	long			start_time;
	bool			is_stop_sim;
	sem_t			*forks;
	sem_t			*sem_sit;
	sem_t			*write_lock;
	sem_t			*state_lock;
}	t_info;
typedef struct s_philo
{
	int				id;
	long			eat_count;
	long			time_last_eat;
	pthread_t		thread;
	void			*left_fork;
	void			*right_fork;
	void			*last_eat_lock;
	sem_t			*sem_meal;
	char			*meal_sem_name;
	t_info			*info;
	t_domain_ops	*ops;
}	t_philo;
#endif
