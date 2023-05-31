/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angassin <angassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 17:30:28 by angassin          #+#    #+#             */
/*   Updated: 2023/05/31 19:32:16 by angassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	thread_create(char **argv, t_symposium *s);
static int	thread_wait(char **argv, t_symposium *s);

/*
	Program that creates threads that share mutual exclusion synchronization 
	primitives, a kind of locks
*/
int	main(int argc, char **argv)
{
	t_symposium	s;

	if (check_input(argc, argv) != OK)
		return (1);
	if (symposium_init(argc, argv, &s) != OK)
		return (2);
	if (thread_create(argv, &s) != OK)
		return (3);
	if (thread_wait(argv, &s) != OK)
		return (4);
	return (0);
}

void	*philo(void *arg)
{
	t_philo		*p;

	p = arg;
	printf("Hello from thread %d\n", p->id);
	sleep(3);
	printf("Ending thread %d\n", p->id);
	return (arg);
}

int	check_input(int argc, char **argv)
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

static int	thread_create(char **argv, t_symposium *s)
{
	int	i;

	i = 1;
	while (i < ft_atoi(argv[1]) + 1)
	{
		s->philos[i].id = i;
		s->philos[i].symposium = s;
		if (pthread_create(&s->philos[i].p_id, NULL, &philo, &s->philos[i])
			!= OK)
			return (error_exit(s, "could not create thread"));
		i++;
	}
	return (0);
}

static int	thread_wait(char **argv, t_symposium *s)
{
	int	i;

	i = 1;
	while (i <= ft_atoi(argv[1]))
	{
		if (pthread_join(s->philos[i].p_id, NULL) != OK)
			return (error_exit(s, "could not join thread"));
		i++;
	}
	free(s->philos);
	free(s->forks);
	i = 1;
	while (i <= s->nb_philo)
	{
		pthread_mutex_destroy(&s->forks[i]);
		i++;
	}
	return (0);
}
