/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:41:42 by cdutel            #+#    #+#             */
/*   Updated: 2024/06/13 10:47:07 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*to_be_or_not(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;

	return (NULL);
}

int	create_threads(t_philo **ph, t_args *args)
{
	int (cur) = 0;
	args->start_time = get_time();
	while (cur < args->philo_num)
	{
		pthread_create(&((*ph)[cur].ph_thread), NULL, to_be_or_not, &((*ph)[cur]));
		cur ++;
	}
	return (EXIT_SUCCESS);
}
