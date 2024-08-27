/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@42student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:29:07 by cdutel            #+#    #+#             */
/*   Updated: 2024/08/27 15:27:03 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(char **argv)
{
	int (i) = 1;
	long (j) = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= 48 && argv[i][j] <= 57))
			{
				printf("%s%s", argv[i], ERR_MSG_NUM);
				return (-1);
			}
			j++;
		}
		i++;
	}
	i = 1;
	while (argv[i])
	{
		j = ft_atoi(argv[i]);
		if (!(j >= 0 && j <= 2147483647))
			return (printf("%s%s", argv[i], ERR_MSG_INT), -1);
		i++;
	}
	return (0);
}

int	init_datastruct(t_datastruct *data, char **argv)
{
	data->n_philo = ft_atoi(argv[1]);
	data->t_to_die = ft_atoi(argv[2]);
	data->t_to_eat = ft_atoi(argv[3]);
	data->t_to_sleep = ft_atoi(argv[4]);
	data->min_meal = -1;
	if (argv[5])
	{
		data->min_meal = ft_atoi(argv[5]);
		if (data->min_meal == 0)
			return (2);
	}
	data->ph = malloc(sizeof(t_philostruct) * data->n_philo);
	if (!data->ph)
		return (EXIT_FAILURE);
	pthread_mutex_init(&data->print, NULL);
	return (EXIT_SUCCESS);
}

int	init_philosophers(t_datastruct *data)
{
	int i = 0;
	data->starttime = ft_get_time();
	while (i < data->n_philo)
	{
		data->ph[i].datainfos = data;
		data->ph[i].both_fork = 0;
		data->ph[i].pos = i + 1;
		data->ph[i].meal_count = 0;
		data->ph[i].r_fork = NULL;
		pthread_mutex_init(&data->ph[i].l_fork, NULL);
		if (i == 0)
			data->ph[i].r_fork = &data->ph[data->n_philo - 1].l_fork;
		else
			data->ph[i].r_fork = &data->ph[i - 1].l_fork;
		pthread_create(&data->ph[i].thread, NULL, &routine, &data->ph[i]);
		i++;
	}
	i = 0;
	while (i < data->n_philo)
	{
		pthread_join(data->ph[i].thread, NULL);
		i++;
	}
	return (EXIT_SUCCESS);
}
