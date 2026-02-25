#ifndef BONUS_APP_H
# define BONUS_APP_H
# include "bonus_types.h"
int		start_simulation(t_philo *philos, t_info *info);
int		child_runtime(t_philo *philo);
bool	is_simulation_finished(t_philo *philo);
void	set_simulation_stop(t_info *info);
#endif
