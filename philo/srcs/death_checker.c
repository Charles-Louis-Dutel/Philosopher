/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:10:59 by cdutel            #+#    #+#             */
/*   Updated: 2024/09/09 21:38:40 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	death_msg(t_datastruct *data, unsigned long death, int philonum)
{
	if (pthread_mutex_lock(&data->print) == 0)
	{
		printf("%lu %d died\n", death, philonum);
		pthread_mutex_unlock(&data->print);
	}
}

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

void	*check_death(void *datastruct)
{
	t_datastruct	*data;
	int				i;
	unsigned long	death_time;

	data = datastruct;
	while (1)
	{
		if (pthread_mutex_lock(&data->mut_min_meal) == 0)
		{
			if (data->min_meal_check >= data->n_philo)
				return (change_signal_stop(data), pthread_mutex_unlock(&data->mut_min_meal), NULL);
			pthread_mutex_unlock(&data->mut_min_meal);
		}
		i = 0;
		while (i < data->n_philo)
		{
			if (pthread_mutex_lock(&data->ph[i].mut_is_ph_dead) == 0)
			{
				if (data->ph[i].dead == 1)
				{
					death_time = ft_get_time() - data->starttime;
					death_msg(data, death_time, i + 1);
					change_signal_stop(data);
					pthread_mutex_unlock(&data->ph[i].mut_is_ph_dead);
					return (NULL);
				}
				pthread_mutex_unlock(&data->ph[i].mut_is_ph_dead);
			}
			i++;
		}
	}
}


