#include "bonus_presentation.h"
#include "bonus_app.h"
#include <unistd.h>
int	main(int ac, char **av)
{
	t_info	*info;
	t_philo	*philos;
	info = NULL;
	philos = NULL;
	if (ac != 5 && ac != 6)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	if (initialize_simulation(ac, av, &philos, &info) == FAILURE)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	if (start_simulation(philos, info) == FAILURE)
	{
		write(2, "Error\n", 6);
		destroy_simulation(philos, info);
		return (1);
	}
	destroy_simulation(philos, info);
	return (0);
}
