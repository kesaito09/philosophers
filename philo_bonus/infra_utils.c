/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infra_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 19:08:42 by kesaitou          #+#    #+#             */
/*   Updated: 2026/02/19 21:31:09 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "setup_contract.h"

/*
** [Layer] Infra Layer
** このファイルの責務:
** - 最低限のlib関数(ft_callocなど)を提供する
** - 他レイヤが依存する共通補助処理を集約する
** - ログ出力の文字列化/出力処理を提供する
** - ドメインロジックを混在させず、再利用可能な処理に限定する
*/

size_t ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	if (!str)
		return (0);	
	while (str[len])
		len++;
	return (len);	
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*dstp;
	unsigned char	*srcp;

	dstp = (unsigned char *)dest;
	srcp = (unsigned char *)src;
	while (n--)
		*(unsigned char *)dstp++ = *(unsigned char *)srcp++;
	return (dest);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;
	unsigned char	uc;

	p = s;
	uc = c;
	while (n--)
		*p++ = uc;
	return (s);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total_size;
	void	*arr;

	if (size != 0 && nmemb > SIZE_MAX / size)
		return (NULL);
	total_size = nmemb * size;
	arr = malloc(total_size);
	if (!arr)
		return (NULL);
	ft_memset(arr, 0, total_size);
	return (arr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*arr;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	arr = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!arr)
		return (NULL);
	ft_memcpy(arr, s1, s1_len);
	ft_memcpy(arr + s1_len, s2, s2_len);
	arr[s1_len + s2_len] = '\0';
	return (arr);
}

static int	count_len(int nbr)
{
	int			len;
	long long	n;

	len = 0;
	n = nbr;
	if (n <= 0)
	{
		len++;
		n = -n;
	}
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long long	num;
	char		*arr;
	int			len;

	num = n;
	len = count_len(num);
	arr = malloc(sizeof(char) * (len + 1));
	if (!arr)
		return (NULL);
	arr[len] = '\0';
	if (num == 0)
		arr[0] = '0';
	if (num < 0)
	{
		arr[0] = '-';
		num = -num;
	}
	while (num)
	{
		arr[--len] = num % 10 + '0';
		num /= 10;
	}
	return (arr);
}

char	*ft_strdup(const char *s)
{
	char	*arr;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(s);
	arr = malloc(sizeof(char) * (len + 1));
	if (!arr)
		return (NULL);
	while (i < len)
	{
		arr[i] = s[i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}

static const char	*get_message(t_state state)
{
	if (state == TAKE)
		return ("has taken a fork");
	if (state == EAT)
		return ("is eating");
	if (state == SLEEP)
		return ("is sleeping");
	if (state == THINK)
		return ("is thinking");
	if (state == DIE)
		return ("died");
	return ("error");
}

int	logger(t_philo *philo, t_state state)
{
	long			elapsed;
	const char		*msg;

	if (!philo || !philo->info)
		return (FAILURE);
	elapsed = get_time_now() - philo->info->start_time;
	msg = get_message(state);
	printf("%ld %d %s\n", elapsed, philo->id, msg);
	return (SUCCESS);
}
