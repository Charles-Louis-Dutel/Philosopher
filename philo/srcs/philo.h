/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 06:49:41 by cdutel            #+#    #+#             */
/*   Updated: 2024/09/28 13:44:03 by cdutel           ###   ########.fr       */
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
time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]\n"
# define ERR_MSG_PH_NUM "Maximum number of philos nead to be 200 or more \
than 0\n"
# define ERR_MSG_MEAL "Minimum number of meal nead to be 1\n"
# define ERR_MSG_INP "Minimun for eat, sleep or die nead to be at least 60\n"
# define ERR_MSG_INT ": argument must be between 0 and int max\n"
# define ERR_MSG_NUM ": argument must contain only number\n"
# define ERR_MSG_MAL "Cannot allocate memory\n"

# define MSG_FORK "has taken a fork\n"
# define MSG_EAT "is eating\n"
# define MSG_SLEEP "is sleeping\n"
# define MSG_THINK "is thinking\n"

typedef struct s_philostruct
{
	int					pos;
	int					meal_count;
	int					stop;
	unsigned long		last_meal;
	unsigned long		death_time;
	pthread_t			thread;
	pthread_mutex_t		mut_stop;
	pthread_mutex_t		l_fork;
	pthread_mutex_t		*r_fork;
	struct s_datastruct	*datainfos;
}	t_philostruct;

typedef struct s_datastruct
{
	t_philostruct	*ph;
	pthread_t		death_checker;
	pthread_mutex_t	mut_is_meal_reached;
	pthread_mutex_t	mut_is_ph_dead;
	pthread_mutex_t	mut_print;
	int				n_philo;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	int				min_meal;
	int				min_meal_reach;
	int				dead;
	unsigned long	starttime;
}	t_datastruct;

void			*routine(void *philostruct);

/*Death checker*/
void			*check_death(void *data);

/*Init*/
int				init_datastruct(t_datastruct *data, char **argv);
int				init_philosophers(t_datastruct *data);

/*Manage error*/
int				err_msg(char *msg);
void			death_msg(t_datastruct *data, unsigned long death, \
int philonum);
void			meal_reached_msg(t_datastruct *data);

/*Utils*/
int				check_args(char **argv);
long			ft_atoi(const char *str);
int				ft_strlen(char *s);
int				print_infos(t_philostruct *philo, char *msg, int n);
int				case_die_inf_eat(t_philostruct *philo);

/*Routine actions*/
int				philo_pair(t_philostruct *philo);
int				taking_forks(t_philostruct *philo);
int				eating(t_philostruct *philo);
int				sleeping(t_philostruct *philo);
int				thinking(t_philostruct *philo);

/*Routine control*/
int				check_to_continue(t_philostruct *philo);
void			set_dead_after_thinking(t_philostruct *philo);
void			wait_to_start(t_philostruct *philo);
void			*routine(void *philostruct);

/*Time*/
unsigned long	ft_get_time(void);
void			ft_msleep(unsigned long duration);

#endif
