/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 06:48:49 by cdutel            #+#    #+#             */
/*   Updated: 2024/06/12 20:32:01 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	*routine()
// {
// 	printf("prout\n");
// 	return (NULL);
// }


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
				printf("%s: invalid argument\n", argv[i]);
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
			return (printf("%s: argument must be an integer\n", argv[i]), -1);
		i++;
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_args	args;
	t_fork	*forks;
	t_philo	*ph;

	if (argc < 5 || argc > 6)
		return (err_msg(ERR_MSG_ARGS), EXIT_FAILURE);
	if (check_args(argv) == -1)
		return (EXIT_FAILURE);
	init_struct(&args, argv);
	if (create_philos_and_forks(&ph, &forks, &args) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	create_threads(&ph, &args);
	join_threads(&ph, &args);
	free(ph);
	free(forks);
	return (EXIT_SUCCESS);
}


// int	main(int argc, char **argv)
// {
// 	pthread_t	*ph;
// 	t_philo		data;

// 	int (i) = 0;
// 	if (argc == 5 || argc == 6)
// 	{
// 		if (check_args(argv) == -1)
// 			return (1);
// 		init_struct(&data, argv);
// 		ph = malloc(sizeof(pthread_t) * data.n_philo);
// 		while (i < data.n_philo)
// 		{
// 			pthread_create(&ph[i], NULL, &routine, NULL);
// 			i++;
// 		}
// 		i = 0;
// 		while (i < data.n_philo)
// 		{
// 			pthread_join(ph[i], NULL);
// 			i++;
// 		}
// 		free(ph);
// 	}
// }
