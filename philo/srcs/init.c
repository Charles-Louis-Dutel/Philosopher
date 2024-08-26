/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@42student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:29:07 by cdutel            #+#    #+#             */
/*   Updated: 2024/08/26 14:25:53 by cdutel           ###   ########.fr       */
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
