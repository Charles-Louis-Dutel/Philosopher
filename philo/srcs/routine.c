/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@42student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:46:42 by cdutel            #+#    #+#             */
/*   Updated: 2024/08/26 19:11:18 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	taking_forks(t_philostruct	*philo)
{
	int (both_forks) = 0;
	if (philo->pos % 2 == 0)
	{
		if (pthread_mutex_lock(&philo->l_fork) == 0 && pthread_mutex_lock(&philo->datainfos->print) == 0)
		{
			printf("philo number %d has taken his l_fork\n", philo->pos);
			pthread_mutex_unlock(&philo->datainfos->print);
			both_forks++;
		}
		if (pthread_mutex_lock(&philo->r_fork) == 0 && pthread_mutex_lock(&philo->datainfos->print) == 0)
		{
			printf("philo number %d has taken his r_fork\n", philo->pos);
			pthread_mutex_unlock(&philo->datainfos->print);
			both_forks++;
		}
		if (pthread_mutex_lock(&philo->datainfos->print) == 0 && both_forks == 2)
		{
			printf("philo number %d is eating\n", philo->pos);
			ft_usleep(philo->datainfos->t_to_eat);
			pthread_mutex_unlock(&philo->datainfos->print);
		}
		pthread_mutex_unlock(&philo->l_fork);
		pthread_mutex_unlock(&philo->r_fork);
	}
	else
	{
		if (pthread_mutex_lock(&philo->r_fork) == 0 && pthread_mutex_lock(&philo->datainfos->print) == 0)
		{
			printf("philo number %d has taken his r_fork\n", philo->pos);
			pthread_mutex_unlock(&philo->datainfos->print);
			both_forks++;
		}
		if (pthread_mutex_lock(&philo->l_fork) == 0 && pthread_mutex_lock(&philo->datainfos->print) == 0)
		{
			printf("philo number %d has taken his l_fork\n", philo->pos);
			pthread_mutex_unlock(&philo->datainfos->print);
			both_forks++;
		}
		if (pthread_mutex_lock(&philo->datainfos->print) == 0 && both_forks == 2)
		{
			printf("philo number %d is eating\n", philo->pos);
			ft_usleep(philo->datainfos->t_to_eat);
			pthread_mutex_unlock(&philo->datainfos->print);
		}
		pthread_mutex_unlock(&philo->l_fork);
		pthread_mutex_unlock(&philo->r_fork);
	}

}

void	*routine(void *philostruct)
{
	t_philostruct	*philo;

	philo = philostruct;
	taking_forks(philo);
	return (NULL);
}
