/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@42student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:10:59 by cdutel            #+#    #+#             */
/*   Updated: 2024/08/30 15:33:41 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	death_msg(t_datastruct *data, unsigned long checker, int philonum)
{
	if (pthread_mutex_lock(&data->print) == 0)
	{
		printf("%lu %d died\n", checker - data->starttime, philonum);
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
	unsigned long	checker;

	data = datastruct;
	while (1)
	{
		if (pthread_mutex_lock(&data->mut_min_meal) == 0)
		{
			if (data->min_meal_check >= data->n_philo)
				return (pthread_mutex_unlock(&data->mut_min_meal), NULL);;
			pthread_mutex_unlock(&data->mut_min_meal);
		}
		i = 0;
		while (i < data->n_philo)
		{
			if (pthread_mutex_lock(&data->ph[i].mut_last_meal) == 0)
			{
				checker = ft_get_time();
				if (checker - data->ph[i].last_meal >= (unsigned long)data->t_to_die || data->n_philo < 2)
				{
					death_msg(data, checker, i + 1);
					change_signal_stop(data);
					pthread_mutex_unlock(&data->ph[i].mut_last_meal);
					return (NULL);
				}
				pthread_mutex_unlock(&data->ph[i].mut_last_meal);
			}
			i++;
		}
	}
}


	// while (1)
	// {
	// 	i = 0;
	// 	while (i < data->n_philo)
	// 	{
	// 		if (pthread_mutex_lock(&data->ph[i].meal_time) == 0)
	// 		{
	// 			printf("philo num %d last meal in check : %lu\n", i + 1, data->ph[i].last_meal);
	// 			pthread_mutex_unlock(&data->ph[i].meal_time);
	// 		}
	// 		i++;
	// 	}
	// 	ft_usleep(1000);
	// }
