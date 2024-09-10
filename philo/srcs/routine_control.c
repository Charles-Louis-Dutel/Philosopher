/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_control.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:51:35 by cdutel            #+#    #+#             */
/*   Updated: 2024/09/10 19:33:52 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_last_meal_time(t_philostruct *philo)
{
	if (ft_get_time() - philo->last_meal >= (unsigned long)philo->datainfos->t_to_die)
	{
		pthread_mutex_lock(&philo->mut_is_ph_dead);
		philo->dead = 1;
		pthread_mutex_unlock(&philo->mut_is_ph_dead);
		return (1);
	}
	return (0);
}

int	check_to_continue(t_philostruct *philo)
{
	if (check_last_meal_time(philo) == 1)
		return (1);
	pthread_mutex_lock(&philo->mut_stop);
	if (philo->stop == 1)
		return (pthread_mutex_unlock(&philo->mut_stop), 1);
	pthread_mutex_unlock(&philo->mut_stop);
	return (0);
}
