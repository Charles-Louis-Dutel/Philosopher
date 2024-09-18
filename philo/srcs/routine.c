/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:46:42 by cdutel            #+#    #+#             */
/*   Updated: 2024/09/18 16:13:36 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	taking_forks(t_philostruct	*philo)
{
	if (philo->pos % 2 == 0)
	{
		pthread_mutex_lock(&philo->l_fork);
		pthread_mutex_lock(philo->r_fork);
		if (print_infos(philo, "has taken a fork\n", 2) == 1)
		{
			pthread_mutex_unlock(&philo->l_fork);
			pthread_mutex_unlock(philo->r_fork);
			return (1);
		}
	}
	else
	{
		if ((philo->pos == 1 || philo->pos == philo->datainfos->n_philo) && philo->datainfos->n_philo % 2 != 0)
		{
			if (ft_get_time() <= philo->last_meal + philo->datainfos->t_to_eat + philo->datainfos->t_to_sleep)
				ft_msleep(10);
		}
		pthread_mutex_lock(philo->r_fork);
		pthread_mutex_lock(&philo->l_fork);
		if (print_infos(philo, "has taken a fork\n", 2) == 1)
		{
			pthread_mutex_unlock(philo->r_fork);
			pthread_mutex_unlock(&philo->l_fork);
			return (1);
		}
	}
	return (0);
}


static int	eating(t_philostruct *philo)
{
	philo->last_meal = ft_get_time();
	if (print_infos(philo, "is eating\n", 1) == 1)
	{
		pthread_mutex_unlock(&philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (1);
	}
	ft_msleep(philo->datainfos->t_to_eat);
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	philo->meal_count++;
	if (philo->meal_count == philo->datainfos->min_meal)
	{
		if (pthread_mutex_lock(&philo->datainfos->mut_is_meal_reached) == 0)
		{
			philo->datainfos->min_meal_reach++;
			pthread_mutex_unlock(&philo->datainfos->mut_is_meal_reached);
		}
	}
	return (0);
}

static int	sleeping(t_philostruct *philo)
{
	if ((ft_get_time() + (unsigned long)philo->datainfos->t_to_sleep) - philo->last_meal > (unsigned long)philo->datainfos->t_to_die)
	{
		if (pthread_mutex_lock(&philo->datainfos->mut_is_ph_dead) == 0)
		{
			if (philo->datainfos->dead == 0)
			{
				philo->datainfos->dead = philo->pos;
				philo->death_time = ft_get_time() + ((unsigned long)philo->datainfos->t_to_die - ft_get_time());
			}
			pthread_mutex_unlock(&philo->datainfos->mut_is_ph_dead);
			return (1);
		}
	}
	if (print_infos(philo, "is sleeping\n", 1) == 1)
		return (1);
	return (0);
}

static void	wait_to_start(t_philostruct *philo)
{
	if (philo->datainfos->n_philo == 1)
	{
		ft_msleep(philo->datainfos->t_to_die);
		return ;
	}
	while (ft_get_time() <= philo->datainfos->starttime)
		ft_msleep(1);
	philo->last_meal = philo->datainfos->starttime;
	if (philo->pos % 2 == 0)
		ft_msleep(philo->datainfos->t_to_eat / 2);
}

void	*routine(void *philostruct)
{
	t_philostruct	*philo;

	philo = philostruct;
	wait_to_start(philo);
	if (philo->datainfos->n_philo == 1 && check_to_continue(philo) == 1)
		return (NULL);
	while (1)
	{
		if (taking_forks(philo) == 1)
			break ;
		if (eating(philo) == 1)
			break ;
		if (sleeping(philo) == 1)
			break ;
		ft_msleep(philo->datainfos->t_to_sleep);
		if (print_infos(philo, "is thinking\n", 1) == 1)
			break ;
	}
	return (NULL);
}
