/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@42student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 22:25:18 by cdutel            #+#    #+#             */
/*   Updated: 2024/08/27 15:24:49 by cdutel           ###   ########.fr       */
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
	while(s[i])
		i++;
	return (i);
}

void	print_infos(t_philostruct *philo, char *msg)
{
	unsigned long	time;

	time = 0;
	time = ft_get_time() - philo->datainfos->starttime;
	if (pthread_mutex_lock(&philo->datainfos->print) == 0)
	{
		printf("%lu philo number %d %s", time, philo->pos, msg);
		pthread_mutex_unlock(&philo->datainfos->print);
	}
}
