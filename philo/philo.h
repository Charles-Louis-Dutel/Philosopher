/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 06:49:41 by cdutel            #+#    #+#             */
/*   Updated: 2024/06/12 20:29:00 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define ERR_MSG_WRITE "Write error: no space left on device\n"
# define ERR_MSG_ARGS "Incorrect input: Retry with: ./philo number_of_philosophers\
	time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"
# define ERR_MSG_MAL "Cannot allocate memory\n"

typedef struct s_args
{
	size_t	start_time;
	int		death_time;
	int		dead_flag;
	int		eat_time;
	int		must_eat;
	int		philo_num;
	int		sleep_time;
}	t_args;

typedef struct s_fork
{
	int				is_used;
	pthread_mutex_t	fork_lock;
}	t_fork;

typedef struct s_philo
{
	pthread_t	ph_thread;
	int			eat_num;
	int			f_l_taken;
	int			f_r_taken;
	int			n_philo;
	t_fork		*right_f;
	t_fork		*left_f;
	t_args		*cur_args;
}	t_philo;

/*Create_philos*/
int		create_philos_and_forks(t_philo **ph, t_fork **forks, t_args *args);

/*Create_threads*/
int		create_threads(t_philo **ph, t_args *args);

/*Destroy_threads*/
void	join_threads(t_philo **ph, t_args *args);

/*Init_struct*/
int		init_struct(t_args *args, char **argv);

/*Manage_errors*/
void	err_msg(char *error_msg);

/*Utils*/
long	ft_atoi(const char *str);
int		ft_strlen(char *s);
size_t	get_time();

#endif
