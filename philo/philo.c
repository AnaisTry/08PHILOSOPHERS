/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angassin <angassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 23:14:26 by angassin          #+#    #+#             */
/*   Updated: 2023/06/09 16:43:27 by angassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	eat(t_philo *p);
static void		print_state(t_philo *p, const char *message);

/* Routine of the threads */
//printf("%d last meal : %ld\n", p->id, p->last_meal);
//printf("%ld, Ending thread %d\n", get_time(p->dinner), p->id);
static void	*philo(void *arg)
{
	t_philo		*p;

	p = arg;
	while (!p->dinner->dead)
	{
		if (p->id % 2 == EVEN)
			usleep(100);
		if (p->dinner->dead)
			break ;
		if (!eat(p))
			break ;
		if (p->dinner->dead)
			break ;
		print_state(p, "%ld %d is sleeping\n");
		ft_usleep(p->dinner->time_to_sleep);
		if (p->dinner->dead)
			break ;
		print_state(p, "%ld %d is thinking\n");
	}
	return (NULL);
}

int	thread_create(t_symposium *s)
{
	int	i;

	i = 0;
	while (i < s->nb_philo)
	{
		s->philos[i].id = i + 1;
		s->philos[i].dinner = s;
		s->philos[i].left_fork = &s->forks[i];
		s->philos[i].last_meal = s->start;
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
		//printf("destroying fork #%d\n", i);
		pthread_mutex_destroy(&s->forks[i]);
		i++;
	}
	free(s->philos);
	free(s->forks);
	pthread_mutex_destroy(s->death);
	free(s->death);
	return (0);
}

static t_bool	eat(t_philo *p)
{
	pthread_mutex_lock(p->left_fork);
	print_state(p, "%ld %d has taken a fork\n");
	if (p->dinner->nb_philo == 1)
	{
		pthread_mutex_unlock(p->left_fork);
		return (FALSE);
	}
	pthread_mutex_lock(p->right_fork);
	p->last_meal = get_time(p->dinner);
	print_state(p, "%ld %d has taken a fork\n");
	pthread_mutex_lock(p->dinner->death);
	print_state(p, "%ld %d is eating\n");
	pthread_mutex_unlock(p->dinner->death);
	ft_usleep(p->dinner->time_to_eat);
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
	return (TRUE);
}

static void	print_state(t_philo *p, const char *message)
{
	if (!p->dinner->dead)
	{
		printf(message, get_time(p->dinner) - p->dinner->start, p->id);
	}
}
