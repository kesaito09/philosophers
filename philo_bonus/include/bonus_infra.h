#ifndef BONUS_INFRA_H
# define BONUS_INFRA_H
# include "bonus_types.h"
# include <stddef.h>
sem_t			*sem_open_wrapper(char *sem_name, int n);
int				sem_unlink_wrapper(char *sem_name);
int				cleanup_semaphores(t_info *info);
int				retry_sem_wait(sem_t *sem);
long			get_time_now(void);
int				philo_usleep(t_philo *philo, long duration_ms);
int				logger(t_philo *philo, t_state state);
t_domain_ops	*get_domain_ops(void);
void			*ft_calloc(size_t nmemb, size_t size);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memset(void *s, int c, size_t n);
size_t			ft_strlen(const char *str);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_itoa(int n);
char			*ft_strdup(const char *s);
#endif
