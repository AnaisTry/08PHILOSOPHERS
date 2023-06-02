/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angassin <angassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 17:30:28 by angassin          #+#    #+#             */
/*   Updated: 2023/06/02 19:55:37 by angassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	thread_create(t_symposium *s);
static int	thread_wait(t_symposium *s);

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
	if (thread_wait(&s) != OK)
		return (4);
	return (0);
}

void	*philo(void *arg)
{
	t_philo		*p;

	p = arg;
	pthread_mutex_lock(p->left_fork);
	printf("%d has taken a fork\n", p->id);
	pthread_mutex_lock(p->right_fork);
	printf("%d is eating\n", p->id);
	usleep(1000 * p->symposium->time_to_eat);
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
	printf("%d is sleeping\n", p->id);
	usleep(1000 * p->symposium->time_to_sleep);
	printf("%d is thinking\n", p->id);
	usleep(1000000);
	printf("Ending thread %d\n", p->id);
	return (NULL);
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

static int	thread_create(t_symposium *s)
{
	int	i;

	i = 0;
	while (i < s->nb_philo)
	{
		s->philos[i].id = i + 1;
		s->philos[i].symposium = s;
		s->philos[i].left_fork = &s->forks[i];
		if (i == s->nb_philo - 1)
			s->philos[i].right_fork = &s->forks[0];
		else
			s->philos[i].right_fork = &s->forks [i + 1];
		if (pthread_create(&s->philos[i].p_id, NULL, &philo, &s->philos[i])
			!= OK)
			return (error_exit(s, "could not create thread"));
		i++;
	}
	return (0);
}

static int	thread_wait(t_symposium *s)
{
	int	i;

	i = 0;
	while (i < s->nb_philo)
	{
		if (pthread_join(s->philos[i].p_id, NULL) != OK)
			return (error_exit(s, "could not join thread"));
		i++;
	}
	i = 0;
	while (i < s->nb_philo)
	{
		printf("destroying fork #%d\n", i);
		pthread_mutex_destroy(&s->forks[i]);
		i++;
	}
	free(s->philos);
	free(s->forks);
	pthread_mutex_destroy(&s->death);
	return (0);
}
