/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:46:42 by cdutel            #+#    #+#             */
/*   Updated: 2024/09/10 22:52:36 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	taking_forks(t_philostruct	*philo)
{
	// if (philo->pos % 2 == 0)
	// {
	// 	pthread_mutex_lock(philo->r_fork);
	// 	pthread_mutex_lock(&philo->l_fork);
	// }
	// else
	// {
		pthread_mutex_lock(&philo->l_fork);
		pthread_mutex_lock(philo->r_fork);
	//}
	if (print_infos(philo, "has taken a fork\n", 2) == 1)
		return (1);
	return (0);
}


static int	eating(t_philostruct *philo)
{
	philo->last_meal = ft_get_time();
	if (print_infos(philo, "is eating\n", 1) == 1)
		return (1);
	ft_msleep(philo->datainfos->t_to_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(&philo->l_fork);
	philo->meal_count++;
	if (philo->meal_count == philo->datainfos->min_meal)
	{
		pthread_mutex_lock(&philo->datainfos->mut_min_meal);
		philo->datainfos->min_meal_reach++;
		pthread_mutex_unlock(&philo->datainfos->mut_min_meal);
	}
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
	if (philo->pos % 2 == 0)
		ft_msleep(10);
}

void	*routine(void *philostruct)
{
	t_philostruct	*philo;

	philo = philostruct;
	wait_to_start(philo);
	if (check_to_continue(philo) == 1)
		return (NULL);
	while (1)
	{
		if (taking_forks(philo) == 1)
			break ;
		if (eating(philo) == 1)
			break ;
		if (print_infos(philo, "is sleeping\n", 1) == 1)
			break ;
		ft_msleep(philo->datainfos->t_to_sleep);
		if (print_infos(philo, "is thinking\n", 1) == 1)
			break ;
	}
	return (NULL);
}
