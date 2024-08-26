/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@42student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 06:48:49 by cdutel            #+#    #+#             */
/*   Updated: 2024/08/26 18:23:36 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philostruct)
{
	t_philostruct	*philo;

	philo = philostruct;
	printf("philo number %d\n", philo->pos);
	// int i = 0;
	// while (i < 1000000)
	// {
	// 	philo->to_increment++;
	// 	i++;
	// }
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_datastruct	data;

	if (argc < 5 || argc > 6)
		return (err_msg(ERR_MSG_ARGS), EXIT_FAILURE);
	if (check_args(argv) == -1)
		return (EXIT_FAILURE);
	if (init_datastruct(&data, argv) == EXIT_FAILURE)
		return (err_msg(ERR_MSG_MAL), EXIT_FAILURE);
	if (data.min_meal == 0)
		return (EXIT_SUCCESS);
	init_philosophers(&data);
	free(data.ph);
	return (EXIT_SUCCESS);
}

	// int i = 0;
	// while (i < data.n_philo)
	// {
	// 	data.ph[i].pos = i;
	// 	pthread_create(&(data).ph[i].thread, NULL, &routine, &(data).ph[i]);
	// 	i++;
	// }
	// i = 0;
	// while (i < data.n_philo)
	// {
	// 	pthread_join(data.ph[i].thread, NULL);
	// 	i++;
	// }


// int	main(int argc, char **argv)
// {
// 	pthread_t		*ph;
// 	t_datastruct	data;
// 	t_philostruct	philo;

// 	int (i) = 0;
// 	if (argc == 5 || argc == 6)
// 	{
// 		if (argc < 5 || argc > 6)
// 			return (err_msg(ERR_MSG_ARGS), EXIT_FAILURE);
// 		if (check_args(argv) == -1)
// 			return (EXIT_FAILURE);

// 		init_datastruct(&data, argv);
// 		printf("data.n_philo : %d\n", data.n_philo);

// 		ph = malloc(sizeof(pthread_t) * data.n_philo);

// 		philo.to_increment = 0;

// 		/*Create threads*/
// 		while (i < data.n_philo)
// 		{
// 			pthread_create(&ph[i], NULL, &routine, &philo);
// 			i++;
// 		}
// 		i = 0;

// 		/*Close threads*/
// 		while (i < data.n_philo)
// 		{
// 			pthread_join(ph[i], NULL);
// 			i++;
// 		}
// 		printf("res : %d\n", philo.to_increment);
// 		free(ph);
// 	}
// 	return (0);
// }
