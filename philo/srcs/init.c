/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:29:07 by cdutel            #+#    #+#             */
/*   Updated: 2024/09/18 17:00:16 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_datastruct(t_datastruct *data, char **argv)
{
	data->n_philo = ft_atoi(argv[1]);
	if (data->n_philo > 200)
		return (err_msg(ERR_MSG_PH_NUM), 2);
	data->t_to_die = ft_atoi(argv[2]);
	data->t_to_eat = ft_atoi(argv[3]);
	data->t_to_sleep = ft_atoi(argv[4]);
	data->min_meal = -1;
	data->min_meal_reach = 0;
	data->dead = 0;
	if (argv[5])
	{
		data->min_meal = ft_atoi(argv[5]);
		if (data->min_meal == 0)
			return (err_msg(ERR_MSG_MEAL), 2);
	}
	data->ph = malloc(sizeof(t_philostruct) * data->n_philo);
	if (!data->ph)
		return (EXIT_FAILURE);
	pthread_mutex_init(&data->mut_print, NULL);
	pthread_mutex_init(&data->mut_is_meal_reached, NULL);
	pthread_mutex_init(&data->mut_is_ph_dead, NULL);
	return (EXIT_SUCCESS);
}

static void	create_threads(t_datastruct *data)
{
	int (i) = 0;
	data->starttime = ft_get_time() + 100;
	pthread_create(&data->death_checker, NULL, &check_death, data);
	while (i < data->n_philo)
	{
		pthread_create(&data->ph[i].thread, NULL, &routine, &data->ph[i]);
		i++;
	}
}

static void	join_threads(t_datastruct *data)
{
	int (i) = 0;
	while (i < data->n_philo)
	{
		pthread_join(data->ph[i].thread, NULL);
		i++;
	}
	pthread_join(data->death_checker, NULL);
	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_destroy(&data->ph[i].l_fork);
		pthread_mutex_destroy(&data->ph[i].mut_stop);
		i++;
	}
	pthread_mutex_destroy(&data->mut_print);
	pthread_mutex_destroy(&data->mut_is_meal_reached);
	pthread_mutex_destroy(&data->mut_is_ph_dead);
}

int	init_philosophers(t_datastruct *data)
{
	int (i) = 0;
	while (i < data->n_philo)
	{
		data->ph[i].datainfos = data;
		data->ph[i].pos = i + 1;
		data->ph[i].r_fork = NULL;
		data->ph[i].meal_count = 0;
		data->ph[i].stop = 0;
		data->ph[i].death_time = 0;
		pthread_mutex_init(&data->ph[i].mut_stop, NULL);
		pthread_mutex_init(&data->ph[i].l_fork, NULL);
		if (i == 0)
			data->ph[i].r_fork = &data->ph[data->n_philo - 1].l_fork;
		else
			data->ph[i].r_fork = &data->ph[i - 1].l_fork;
		i++;
	}
	create_threads(data);
	join_threads(data);
	return (EXIT_SUCCESS);
}
