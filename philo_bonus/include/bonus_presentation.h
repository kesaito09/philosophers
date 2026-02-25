#ifndef BONUS_PRESENTATION_H
# define BONUS_PRESENTATION_H
# include "bonus_types.h"
int		parse_input(int ac, char **av, t_info *info);
int		initialize_simulation(int ac, char **av, t_philo **philos,
			t_info **info);
t_philo	*init_philo(t_info *info);
void	destroy_simulation(t_philo *philos, t_info *info);
#endif
