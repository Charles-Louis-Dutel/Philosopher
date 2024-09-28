/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_control.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:51:35 by cdutel            #+#    #+#             */
/*   Updated: 2024/09/28 14:00:03 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_last_meal_time(t_philostruct *philo)
{
	if (ft_get_time() - philo->last_meal >= \
	(unsigned long)philo->datainfos->t_to_die)
	{
		if (pthread_mutex_lock(&philo->datainfos->mut_is_ph_dead) == 0)
		{
			if (philo->datainfos->dead == 0)
			{
				philo->datainfos->dead = philo->pos;
				philo->death_time = ft_get_time() - philo->datainfos->starttime;
			}
			pthread_mutex_unlock(&philo->datainfos->mut_is_ph_dead);
			return (1);
		}
	}
	return (0);
}

int	check_to_continue(t_philostruct *philo)
{
	if (check_last_meal_time(philo) == 1)
		return (1);
	if (pthread_mutex_lock(&philo->mut_stop) == 0)
	{
		if (philo->stop == 1)
			return (pthread_mutex_unlock(&philo->mut_stop), 1);
		pthread_mutex_unlock(&philo->mut_stop);
	}
	return (0);
}

void	set_dead_after_thinking(t_philostruct *philo)
{
	if (pthread_mutex_lock(&philo->datainfos->mut_is_ph_dead) == 0)
	{
		if (philo->datainfos->dead == 0)
		{
			philo->datainfos->dead = philo->pos;
			philo->death_time = philo->datainfos->t_to_die;
		}
		pthread_mutex_unlock(&philo->datainfos->mut_is_ph_dead);
	}
}

void	wait_to_start(t_philostruct *philo)
{
	int (waittime) = philo->datainfos->t_to_eat;
	if (philo->datainfos->t_to_eat > philo->datainfos->t_to_die)
		waittime = philo->datainfos->t_to_die;
	if (philo->datainfos->n_philo == 1)
	{
		if (pthread_mutex_lock(&philo->datainfos->mut_is_ph_dead) == 0)
		{
			philo->datainfos->dead = philo->pos;
			philo->death_time = philo->datainfos->t_to_die;
			ft_msleep(philo->datainfos->t_to_die);
			pthread_mutex_unlock(&philo->datainfos->mut_is_ph_dead);
			return ;
		}
	}
	while (ft_get_time() <= philo->datainfos->starttime)
		ft_msleep(1);
	philo->last_meal = philo->datainfos->starttime;
	if (philo->pos % 2 == 0)
		ft_msleep(waittime / 2);
	if (philo->datainfos->n_philo % 2 != 0 && \
	philo->pos == philo->datainfos->n_philo && \
	philo->datainfos->t_to_eat > philo->datainfos->t_to_sleep)
		ft_msleep(waittime);
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
		if (thinking(philo) == 1)
			break ;
		if (philo->datainfos->t_to_eat * 2 > philo->datainfos->t_to_die)
			return (set_dead_after_thinking(philo), NULL);
	}
	return (NULL);
}
