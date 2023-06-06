/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angassin <angassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 17:30:28 by angassin          #+#    #+#             */
/*   Updated: 2023/06/06 12:56:49 by angassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	input_check(int argc, char **argv);
static void	check_if_dead(t_symposium *s);

/*
	Program that creates threads that share mutual exclusion synchronization 
	primitives, a kind of locks, implementing a concurrent algorithm to solve 
	the dining philosophers problem : 
	https://en.wikipedia.org/wiki/Dining_philosophers_problem
*/
int	main(int argc, char **argv)
{
	t_symposium	s;

	if (input_check(argc, argv) != OK)
		return (1);
	if (symposium_init(argc, argv, &s) != OK)
		return (2);
	if (thread_create(&s) != OK)
		return (3);
	check_if_dead(&s);
	if (thread_wait(&s) != OK)
		return (4);
	return (0);
}

/*
	Checks number of arguments and that the value of each argument
	is bigger than 0
*/
static int	input_check(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		printf("Usage : number_of_philosophers time_to_die time_to_eat"
			" time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	printf("nb philo : %d\n", ft_atoi(argv[1]));
	i = 1;
	while (i < argc)
	{
		if (ft_atoi(argv[i]) <= 0)
			return (2);
		i++;
	}
	return (0);
}

static void	check_if_dead(t_symposium *s)
{
	int			i;

	while (TRUE)
	{
		i = 0;
		while (i < s->nb_philo)
		{
			if (s->philos[i].last_meal - s->start > s->time_to_die)
			{
				s->dead = TRUE;
				printf("%ld %d died\n", get_time(s), s->philos[i].id);
				break ;
			}
			i++;
		}
		if (s->dead == TRUE)
			break ;
	}
}
