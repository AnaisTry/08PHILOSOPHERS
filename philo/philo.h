/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angassin <angassin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 17:27:34 by angassin          #+#    #+#             */
/*   Updated: 2023/06/02 23:27:17 by angassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*									[Includes]								*/

# include <pthread.h>
// printf
# include <stdio.h>
// malloc, free
# include <limits.h>
# include <stdlib.h>
// usleep
# include <unistd.h>
// gettimeofday
# include <sys/time.h>

/*									[Macros]								*/

# define OK 0
# define TRUE 1

/*									[Typedefs]								*/

typedef struct s_symposium	t_symposium;
typedef struct s_philo
{
	int						id;
	pthread_t				p_id;
	int						last_meal;
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			*right_fork;
	t_symposium				*symposium;
}							t_philo;

struct						s_symposium
{
	int						nb_philo;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						nb_meals;
	unsigned long			start;
	t_philo					*philos;
	pthread_mutex_t			*forks;
	pthread_mutex_t			death;
};

/*									[Src]									*/

// init.c
int		symposium_init(int argc, char **argv, t_symposium *s);

// philo.c
int		thread_create(t_symposium *s);
int		thread_wait(t_symposium *s);

/*									[Utils]									*/

int		ft_atoi(const char *str);
int		error_exit(t_symposium *s, char *message);

#endif
