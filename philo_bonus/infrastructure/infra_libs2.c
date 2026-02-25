#include "bonus_infra.h"
#include <stdlib.h>
static int	count_len(int nbr)
{
	int		len;
	long	n;
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
	long	num;
	char	*arr;
	int		len;
	num = n;
	len = count_len(n);
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
		arr[--len] = (num % 10) + '0';
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
