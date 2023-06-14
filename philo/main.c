/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angassin <angassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 17:30:28 by angassin          #+#    #+#             */
/*   Updated: 2023/06/14 18:21:26 by angassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int		check_input(int argc, char **argv);
static void		check_if_stop(t_symposium *s);
static void		philo_dies(t_philo *p, t_bool status);
static t_bool	is_full(t_philo *p);

/*
	Program that creates threads that share mutual exclusion synchronization 
	primitives, a kind of locks, implementing a concurrent algorithm to solve 
	the dining philosophers problem : 
	https://en.wikipedia.org/wiki/Dining_philosophers_problem
*/
int	main(int argc, char **argv)
{
	t_symposium	s;

	if (check_input(argc, argv) != OK)
		return (1);
	if (symposium_init(argc, argv, &s) != OK)
		return (2);
	if (thread_create(&s) != OK)
		return (3);
	check_if_stop(&s);
	if (thread_wait(&s) != OK)
		return (4);
	return (0);
}

/*
	Checks number of arguments, that the type is correct and that
	the value of each argument is bigger than 0
	printf("nb philo : %d\n", ft_atoi(argv[1]));
*/
static int	check_input(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
	{
		printf("Usage : number_of_philosophers time_to_die time_to_eat"
			" time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (ft_isdigit(argv[i][j]) == FALSE)
				return (2);
			j++;
		}
		if (ft_atoi(argv[i]) <= 0)
			return (3);
		i++;
	}
	return (0);
}

/*
	Loops repetitively on the threads as long as one philo isn't dead
	or, if the condition is given, and they are still alive,
	as long as they have not all eaten at least 
	number_of_times_each_philosopher_must_eat.
	Locks the death mutex the time to print who is dead
*/
static void	check_if_stop(t_symposium *s)
{
	int	i;

	while (TRUE)
	{
		s->all_full = 0;
		i = 0;
		while (i < s->nb_philo)
		{
			if (get_time() - s->philos[i].last_meal > s->time_to_die)
			{
				philo_dies(&s->philos[i], TRUE);
				break ;
			}
			if (is_full(&s->philos[i]))
				s->all_full++;
			if (s->all_full == s->nb_philo)
			{
				philo_dies(&s->philos[i], FALSE);
				break ;
			}
			++i;
		}
		if (s->dead == TRUE)
			break ;
	}
}

static void	philo_dies(t_philo *p, t_bool status)
{
	pthread_mutex_lock(p->dinner->death);
	p->dinner->dead = TRUE;
	if (status == TRUE)
		printf("%ld %d died\n", get_time() - p->dinner->start, p->id);
	pthread_mutex_unlock(p->dinner->death);
}

static t_bool	is_full(t_philo *p)
{
	if (p->nb_meals >= p->dinner->max_nb_meals
		&& p->dinner->max_nb_meals != INFINITE)
		return (TRUE);
	return (FALSE);
}
