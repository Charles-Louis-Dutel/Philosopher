/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 06:49:41 by cdutel            #+#    #+#             */
/*   Updated: 2024/09/10 22:31:43 by cdutel           ###   ########.fr       */
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
# define ERR_MSG_ARGS "Incorrect input: Retry with: ./philo number_of_philosophers \
time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"
# define ERR_MSG_INT ": argument must be between 0 and int max\n"
# define ERR_MSG_NUM ": argument must contain only number\n"
# define ERR_MSG_MAL "Cannot allocate memory\n"


typedef struct s_philostruct
{
	int					pos;
	int					meal_count;
	int					dead;
	int					stop;
	unsigned long		last_meal;
	pthread_t			thread;
	pthread_mutex_t		mut_is_ph_dead;
	pthread_mutex_t		mut_stop;
	pthread_mutex_t		l_fork;
	pthread_mutex_t		*r_fork;
	struct s_datastruct	*datainfos;
}	t_philostruct;

typedef struct s_datastruct
{
	t_philostruct	*ph;
	pthread_t		death_check;
	pthread_mutex_t	mut_print;
	pthread_mutex_t	mut_min_meal;
	int				n_philo;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	int				min_meal;
	int				min_meal_reach;
	unsigned long	start;
	unsigned long	starttime;
}	t_datastruct;

void			*routine(void *philostruct);

/*Death checker*/
void			*check_death(void *data);

/*Init*/
int				check_args(char **argv);
int				init_datastruct(t_datastruct *data, char **argv);
int				init_philosophers(t_datastruct *data);

/*Manage error*/
int				err_msg(char *msg);

/*Utils*/
long			ft_atoi(const char *str);
void			ft_bzero(void *s, size_t n);
int				ft_strlen(char *s);
int				print_infos(t_philostruct *philo, char *msg, int n);

/*Routine*/
void			*routine(void *philostruct);

/*Routine control*/
int				check_to_continue(t_philostruct *philo);

/*Time*/
unsigned long	ft_get_time(void);
void			ft_msleep(unsigned long duration);

#endif
