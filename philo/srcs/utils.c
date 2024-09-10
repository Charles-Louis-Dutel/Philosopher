/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 22:25:18 by cdutel            #+#    #+#             */
/*   Updated: 2024/09/10 19:36:47 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	nb;

	i = 0;
	nb = 0;
	sign = 1;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			sign *= -sign;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		nb = (nb * 10) + (str[i] - '0');
		i++;
	}
	return (nb * sign);
}

int	ft_strlen(char *s)
{
	int (i) = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_bzero(void *s, size_t n)
{
	char			*str;
	unsigned long	i;

	i = 0;
	str = s;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

int	print_infos(t_philostruct *philo, char *msg, int n)
{
	unsigned long (time) = 0;
	pthread_mutex_lock(&philo->datainfos->mut_print);
	if (check_to_continue(philo) == 1)
		return (pthread_mutex_unlock(&philo->datainfos->mut_print), 1);
	time = ft_get_time() - philo->datainfos->starttime;
	if (n == 1)
		printf("%lu %d %s", time, philo->pos, msg);
	else if (n == 2)
	{
		while (n > 0)
		{
			printf("%lu %d %s", time, philo->pos, msg);
			n--;
		}
	}
	pthread_mutex_unlock(&philo->datainfos->mut_print);
	return (0);
}
