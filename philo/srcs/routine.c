/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:46:42 by cdutel            #+#    #+#             */
/*   Updated: 2024/09/09 23:21:45 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	taking_forks(t_philostruct	*philo)
{
	int	time;

	if (philo->pos % 2 == 0)
	{
		if (pthread_mutex_lock(&philo->l_fork) == 0)
		{
			time = ft_get_time() - philo->datainfos->starttime;
			if (print_infos(philo, "has taken a fork\n", time) == 1)
				return (pthread_mutex_unlock(&philo->l_fork), 1);
		}
		if (pthread_mutex_lock(philo->r_fork) == 0)
		{
			time = ft_get_time() - philo->datainfos->starttime;
			if (print_infos(philo, "has taken a fork\n", time) == 1)
				return (pthread_mutex_unlock(&philo->l_fork), pthread_mutex_unlock(philo->r_fork), 1);
		}
	}
	else
	{
		ft_usleep(10);
		if (pthread_mutex_lock(philo->r_fork) == 0)
		{
			time = ft_get_time() - philo->datainfos->starttime;
			if (print_infos(philo, "has taken a fork\n", time) == 1)
				return (pthread_mutex_unlock(philo->r_fork), 1);
		}
		if (pthread_mutex_lock(&philo->l_fork) == 0)
		{
			time = ft_get_time() - philo->datainfos->starttime;
			if (print_infos(philo, "has taken a fork\n", time) == 1)
				return (pthread_mutex_unlock(philo->r_fork), pthread_mutex_unlock(&philo->l_fork), 1);
		}
	}
	return (0);
}


static int	eating(t_philostruct *philo)
{
	philo->last_meal = ft_get_time();
	print_infos(philo, "is eating\n", philo->last_meal - philo->datainfos->starttime);
	ft_usleep(philo->datainfos->t_to_eat);
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
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
	return (0);
}

static void	wait_to_start(t_philostruct *philo)
{
	if (philo->datainfos->n_philo == 1)
		ft_usleep(philo->datainfos->t_to_die);
	while (1)
	{
		if (pthread_mutex_lock(&philo->datainfos->mut_start) == 0)
		{
			pthread_mutex_unlock(&philo->datainfos->mut_start);
			break ;
		}
	}
}

void	*routine(void *philostruct)
{
	t_philostruct	*philo;
	int				time;

	philo = philostruct;
	wait_to_start(philo);
	while (1)
	{
		if (taking_forks(philo) == 1)
			break ;
		if (eating(philo) == 1)
			break ;
		time = ft_get_time() - philo->datainfos->starttime;
		if (print_infos(philo, "is sleeping\n", time) == 1)
			break ;
		ft_usleep(philo->datainfos->t_to_sleep);
		time = ft_get_time() - philo->datainfos->starttime;
		if (print_infos(philo, "is thinking\n", time) == 1)
			break ;
	}
	//printf("%lu philo num %d end\n", ft_get_time() - philo->datainfos->starttime, philo->pos);
	return (NULL);
}
