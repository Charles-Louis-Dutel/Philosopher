/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_threads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:27:49 by cdutel            #+#    #+#             */
/*   Updated: 2024/06/12 20:34:35 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_threads(t_philo **ph, t_args *args)
{
	int (cur) = 0;
	while (cur < args->philo_num)
	{
		pthread_join((*ph)[cur].ph_thread, NULL);
		cur++;
	}
}
