/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angassin <angassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:02:29 by angassin          #+#    #+#             */
/*   Updated: 2023/06/02 14:37:31 by angassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	symposium_init(int argc, char **argv, t_symposium *s)
{	
	s->nb_philo = ft_atoi(argv[1]);
	s->forks = NULL;
	s->philos = malloc(sizeof(*s->philos) * s->nb_philo);
	if (s->philos == NULL)
		return (error_exit(s, "Could not allocate the array of threads"));
	s->forks = malloc(sizeof(*s->forks) * s->nb_philo);
	if (s->forks == NULL)
		return (error_exit(s, "Could not allocate the array of mutexes"));
	s->time_to_die = ft_atoi(argv[2]);
	s->time_to_eat = ft_atoi(argv[3]);
	s->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		s->nb_meals = ft_atoi(argv[5]);
	mutexes_init(s);
	return (0);
}

int	mutexes_init(t_symposium *s)
{
	int	i;

	i = 0;
	while (i < s->nb_philo)
	{
		if (pthread_mutex_init(&s->forks[i], NULL) != OK)
			return (error_exit(s, "Initialisation of forks failed"));
		i++;
	}
	if (pthread_mutex_init(&s->death, NULL) != OK)
		return (error_exit(s, "Initialisation of death failed"));
	return (0);
}
