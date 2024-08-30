/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@42student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:46:42 by cdutel            #+#    #+#             */
/*   Updated: 2024/08/30 15:46:23 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_to_continue(t_philostruct *philo)
{
	if (pthread_mutex_lock(&philo->mut_stop) == 0)
	{
		if (philo->stop == 1)
		{
			pthread_mutex_unlock(&philo->mut_stop);
			return (1);
		}
		pthread_mutex_unlock(&philo->mut_stop);
	}
	if (pthread_mutex_lock(&philo->datainfos->mut_min_meal) == 0)
	{
		if (philo->datainfos->min_meal_check == philo->datainfos->n_philo)
		{
			pthread_mutex_unlock(&philo->datainfos->mut_min_meal);
			return (1);
		}
		pthread_mutex_unlock(&philo->datainfos->mut_min_meal);
	}
	return (0);
}

static int	taking_forks(t_philostruct	*philo)
{
	if (philo->pos % 2 == 0)
	{
		if (pthread_mutex_lock(&philo->l_fork) == 0)
		{
			if (print_infos(philo, "has taken a fork\n") == 1)
				return (pthread_mutex_unlock(&philo->l_fork), 1);
		}
		if (pthread_mutex_lock(philo->r_fork) == 0)
		{
			if (print_infos(philo, "has taken a fork\n") == 1)
				return (pthread_mutex_unlock(&philo->l_fork), pthread_mutex_unlock(philo->r_fork), 1);
		}
	}
	else
	{
		if (pthread_mutex_lock(philo->r_fork) == 0)
		{
			if (print_infos(philo, "has taken a fork\n") == 1)
				return (pthread_mutex_unlock(philo->r_fork), 1);
		}
		if (pthread_mutex_lock(&philo->l_fork) == 0)
		{
			if (print_infos(philo, "has taken a fork\n") == 1)
				return (pthread_mutex_unlock(philo->r_fork), pthread_mutex_unlock(&philo->l_fork), 1);
		}
	}
	return (0);
}

static int	eating(t_philostruct *philo)
{
	if (pthread_mutex_lock(&philo->mut_last_meal) == 0)
	{
		philo->last_meal = ft_get_time();
		pthread_mutex_unlock(&philo->mut_last_meal);
	}
	if (print_infos(philo, "is eating\n") == 1)
		return (1);
	ft_usleep(philo->datainfos->t_to_eat);
	philo->meal_count++;
	if (philo->meal_count == philo->datainfos->min_meal)
	{
		if (pthread_mutex_lock(&philo->datainfos->mut_min_meal) == 0)
		{
			//printf("POS %d MIN MEAL REACH\n", philo->pos);
			philo->datainfos->min_meal_check++;
			pthread_mutex_unlock(&philo->datainfos->mut_min_meal);
		}
	}
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (0);
}

void	*routine(void *philostruct)
{
	t_philostruct	*philo;

	philo = philostruct;
	while (1)
	{
		if (taking_forks(philo) == 1)
			break;
		if (eating(philo) == 1)
			break;
		if (print_infos(philo, "is sleeping\n") == 1)
			break;
		ft_usleep(philo->datainfos->t_to_sleep);
		if (print_infos(philo, "is thinking\n") == 1)
			break;
	}
	//printf("%lu philo num %d end\n", ft_get_time() - philo->datainfos->starttime, philo->pos);
	return (NULL);
}
