/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:11:20 by cdutel            #+#    #+#             */
/*   Updated: 2024/06/12 18:51:48 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philo(int cur, t_philo *ph, t_fork **forks, t_args *args)
{
	ph->cur_args = args;
	ph->n_philo = cur;
	ph->f_l_taken = 0;
	ph->f_r_taken = 0;
	ph->eat_num = 0;
	ph->right_f = &((*forks)[cur]);
	if (cur == args->philo_num - 1)
		ph->left_f = &((*forks)[0]);
	else
		ph->left_f = &((*forks)[cur + 1]);
}

int	create_philos_and_forks(t_philo **ph, t_fork **forks, t_args *args)
{
	int	(cur) = 0;
	*ph = malloc(args->philo_num * sizeof(t_philo));
	if (!(*ph))
		return (err_msg(ERR_MSG_MAL), EXIT_FAILURE);
	*forks = malloc(args->philo_num * sizeof(t_philo));
	if (!(*forks))
		return (err_msg(ERR_MSG_MAL), free(*ph), EXIT_FAILURE);
	while (cur < args->philo_num)
	{
		init_philo(cur, &(*ph)[cur], forks, args);
		cur++;
	}
	return (EXIT_SUCCESS);
}
