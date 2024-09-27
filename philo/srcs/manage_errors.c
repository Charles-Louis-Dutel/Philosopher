/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 09:17:00 by cdutel            #+#    #+#             */
/*   Updated: 2024/09/27 14:56:53 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	err_msg(char *msg)
{
	if (write(2, msg, ft_strlen(msg)) == -1)
	{
		write(2, ERR_MSG_WRITE, ft_strlen(ERR_MSG_WRITE));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	death_msg(t_datastruct *data, unsigned long death, int philonum)
{
	if (pthread_mutex_lock(&data->mut_print) == 0)
	{
		printf("%lu %d died\n", death, philonum);
		pthread_mutex_unlock(&data->mut_print);
	}
}

void	meal_reached_msg(t_datastruct *data)
{
	if (pthread_mutex_lock(&data->mut_print) == 0)
	{
		printf("All philosophers have eaten %d times\n", data->min_meal);
		pthread_mutex_unlock(&data->mut_print);
	}
}
