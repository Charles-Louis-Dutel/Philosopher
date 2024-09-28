/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:10:59 by cdutel            #+#    #+#             */
/*   Updated: 2024/09/28 13:52:21 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	change_signal_stop(t_datastruct *data)
{
	int (i) = 0;
	while (i < data->n_philo)
	{
		if (pthread_mutex_lock(&data->ph[i].mut_stop) == 0)
		{
			data->ph[i].stop = 1;
			pthread_mutex_unlock(&data->ph[i].mut_stop);
		}
		i++;
	}
}

int	check_meal(t_datastruct *data)
{
	if (pthread_mutex_lock(&data->mut_is_meal_reached) == 0)
	{
		if (data->min_meal_reach == data->n_philo)
		{
			pthread_mutex_unlock(&data->mut_is_meal_reached);
			change_signal_stop(data);
			meal_reached_msg(data);
			return (1);
		}
		pthread_mutex_unlock(&data->mut_is_meal_reached);
	}
	return (0);
}

static void	wait_time(t_datastruct *data)
{
	unsigned long	deathtime;
	unsigned long	waittime;

	deathtime = data->ph[data->dead - 1].death_time;
	waittime = (ft_get_time() - data->starttime);
	if (deathtime > waittime)
		ft_msleep(deathtime - waittime);
	change_signal_stop(data);
	death_msg(data, deathtime, data->dead);
}

void	*check_death(void *datastruct)
{
	t_datastruct	*data;

	data = datastruct;
	while (ft_get_time() <= data->starttime)
		ft_msleep(1);
	while (1)
	{
		if (pthread_mutex_lock(&data->mut_is_ph_dead) == 0)
		{
			if (data->dead > 0)
			{
				pthread_mutex_unlock(&data->mut_is_ph_dead);
				wait_time(data);
				return (NULL);
			}
			pthread_mutex_unlock(&data->mut_is_ph_dead);
			ft_msleep(1);
		}
		if (data->min_meal > 0 && check_meal(data) == 1)
			return (NULL);
	}
	return (NULL);
}
