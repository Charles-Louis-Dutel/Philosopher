/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@42student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:46:42 by cdutel            #+#    #+#             */
/*   Updated: 2024/08/27 15:44:50 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	taking_forks(t_philostruct	*philo)
{
	if (philo->pos % 2 == 0)
	{
		if (pthread_mutex_lock(&philo->l_fork) == 0)
		{
			print_infos(philo, "has taken his l_fork\n");
			philo->both_fork++;
		}
		if (pthread_mutex_lock(philo->r_fork) == 0)
		{
			print_infos(philo, "has taken his r_fork\n");
			philo->both_fork++;
		}
	}
	else
	{
		if (pthread_mutex_lock(philo->r_fork) == 0)
		{
			print_infos(philo, "has taken his r_fork\n");
			philo->both_fork++;
		}
		if (pthread_mutex_lock(&philo->l_fork) == 0)
		{
			print_infos(philo, "has taken his l_fork\n");
			philo->both_fork++;
		}
	}

}

static void	eating(t_philostruct *philo)
{
	if (philo->both_fork == 2)
	{
		print_infos(philo, "is eating\n");
		philo->meal_count++;
		ft_usleep(philo->datainfos->t_to_eat);
		pthread_mutex_unlock(&philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		philo->both_fork = 0;
	}
}

void	*routine(void *philostruct)
{
	t_philostruct	*philo;

	philo = philostruct;
	while (1)
	{
		taking_forks(philo);
		eating(philo);
		print_infos(philo, "is sleeping\n");
		ft_usleep(philo->datainfos->t_to_sleep);
		print_infos(philo, "is thinking\n");
	}
	return (NULL);
}
