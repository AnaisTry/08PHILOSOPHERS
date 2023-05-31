/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angassin <angassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:00:36 by angassin          #+#    #+#             */
/*   Updated: 2023/05/30 18:27:58 by angassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo/philo.h"

static int	thread_create(char **argv, pthread_t *p, int *p_nb);
static int	thread_wait(char **argv, pthread_t *p, int *p_nb);


int	main(int argc, char **argv)
{
	pthread_t	*p;
	int			*p_nb;

	if (check_input(argc, argv) != OK)
		return (1);
	p_nb = NULL;
	p = malloc(sizeof(pthread_t) * 200);
	if (thread_create(argv, p, p_nb) != OK)
		return (2);
	if (thread_wait(argv, p, p_nb) != OK)
		return (3);
	return (0);
}

void	*philo(void *arg)
{
	int	i;

	i = *(int *)arg;
	printf("Hello from thread %d\n", i);
	sleep(3);
	printf("Ending thread %d\n", i);
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

static int	thread_create(char **argv, pthread_t *p, int *p_nb)
{
	int	i;

	i = 1;
	while (i < ft_atoi(argv[1]) + 1)
	{
		p_nb = malloc(sizeof(int));
		if (p_nb == NULL)
			return (2);
		*p_nb = i;
		if (pthread_create(&p[i], NULL, &philo, p_nb) != OK)
			return (error_exit(p_nb, "could not create thread\n"));
		i++;
	}
	return (0);
}

static int	thread_wait(char **argv, pthread_t *p, int *p_nb)
{
	int	i;

	i = 1;
	while (i < ft_atoi(argv[1]) + 1)
	{
		if (pthread_join(p[i], (void **)&p_nb) != OK)
			return (error_exit(p_nb, "could not join thread\n"));
		i++;
		free(p_nb);
	}
	return (0);
}