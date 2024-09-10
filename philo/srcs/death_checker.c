/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:10:59 by cdutel            #+#    #+#             */
/*   Updated: 2024/09/10 19:58:37 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	death_msg(t_datastruct *data, unsigned long death, int philonum)
{
	pthread_mutex_lock(&data->mut_print);
	printf("%lu %d died\n", death, philonum);
	pthread_mutex_unlock(&data->mut_print);
}

static void	change_signal_stop(t_datastruct *data)
{
	int (i) = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_lock(&data->ph[i].mut_stop);
		data->ph[i].stop = 1;
		pthread_mutex_unlock(&data->ph[i].mut_stop);
		i++;
	}
}

void	*check_death(void *datastruct)
{
	t_datastruct	*data;
	int				i;
	//unsigned long	death_time;

	data = datastruct;
	ft_msleep(150);
	while (1)
	{
		pthread_mutex_lock(&data->mut_min_meal);
		if (data->min_meal_reach >= data->n_philo)
			return (change_signal_stop(data), pthread_mutex_unlock(&data->mut_min_meal), NULL);
		pthread_mutex_unlock(&data->mut_min_meal);
		i = 0;
		while (i < data->n_philo)
		{
			pthread_mutex_lock(&data->ph[i].mut_is_ph_dead);
			if (data->ph[i].dead == 1)
			{
				death_msg(data, ft_get_time() - data->starttime, i + 1);
				change_signal_stop(data);
				return (change_signal_stop(data), pthread_mutex_unlock(&data->ph[i].mut_is_ph_dead), NULL);
			}
			pthread_mutex_unlock(&data->ph[i].mut_is_ph_dead);
			i++;
		}
	}
	return (NULL);
}


