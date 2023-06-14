/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angassin <angassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 18:02:15 by angassin          #+#    #+#             */
/*   Updated: 2023/06/14 18:02:39 by angassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_exit(t_symposium *s, char *message, int status)
{
	int	i;

	i = 0;
	if (status > 0)
	{
		while (i < status && i < s->nb_philo)
		{
			pthread_mutex_destroy(&s->forks[i]);
			i++;
		}
		if (i < status)
			pthread_mutex_destroy(s->death);
		if (i < status)
			pthread_mutex_destroy(s->print);
	}
	free(s->philos);
	free(s->forks);
	free(s->death);
	free(s->print);
	printf("%s\n", message);
	return (-1);
}
