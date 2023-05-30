/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angassin <angassin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 17:27:34 by angassin          #+#    #+#             */
/*   Updated: 2023/05/30 13:17:18 by angassin         ###   ########.fr       */
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

/*									[Macros]								*/

# define OK 0
# define CHILD 0

/*									[Typedefs]								*/

typedef struct s_philo
{
	int				id;
	pthread_t		p_id;
}					t_philo;

typedef struct s_symposium
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meals;
	t_philo			*philos;

}					t_symposium;

/*									[Src]									*/

void				*philo(void *arg);
int					check_input(int argc, char **argv);
int					error_exit(void *arg, char *message);

/*									[Utils]									*/

int					ft_atoi(const char *str);

#endif
