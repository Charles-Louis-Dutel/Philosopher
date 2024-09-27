/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 22:25:18 by cdutel            #+#    #+#             */
/*   Updated: 2024/09/27 15:03:00 by cdutel           ###   ########.fr       */
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

int	check_args(char **argv)
{
	int (i) = 1;
	long (j) = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= 48 && argv[i][j] <= 57))
			{
				printf("%s%s", argv[i], ERR_MSG_NUM);
				return (-1);
			}
			j++;
		}
		i++;
	}
	i = 1;
	while (argv[i])
	{
		j = ft_atoi(argv[i]);
		if (!(j >= 0 && j <= 2147483647))
			return (printf("%s%s", argv[i], ERR_MSG_INT), -1);
		i++;
	}
	return (0);
}

int	ft_strlen(char *s)
{
	int (i) = 0;
	while (s[i])
		i++;
	return (i);
}

int	print_infos(t_philostruct *philo, char *msg, int n)
{
	unsigned long (time) = 0;
	if (pthread_mutex_lock(&philo->datainfos->mut_print) == 0)
	{
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
	}
	return (0);
}

void	case_die_inf_eat(t_philostruct *philo)
{
	if (philo->datainfos->t_to_die < philo->datainfos->t_to_eat)
	{
		if (pthread_mutex_lock(&philo->datainfos->mut_is_ph_dead) == 0)
		{
			if (philo->datainfos->dead == 0)
			{
				philo->datainfos->dead = philo->pos;
				philo->death_time = (unsigned long)philo->datainfos->t_to_die;
			}
			pthread_mutex_unlock(&philo->datainfos->mut_is_ph_dead);
		}
	}
}
