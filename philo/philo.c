/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angassin <angassin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 23:14:26 by angassin          #+#    #+#             */
/*   Updated: 2023/06/02 23:22:18 by angassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philo(void *arg)
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
	printf("Ending thread %d\n", p->id);
	return (NULL);
}

int	thread_create(t_symposium *s)
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

int	thread_wait(t_symposium *s)
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