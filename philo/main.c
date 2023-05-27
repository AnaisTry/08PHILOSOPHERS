/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angassin <angassin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 17:30:28 by angassin          #+#    #+#             */
/*   Updated: 2023/05/27 18:17:51 by angassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	
*/
int	main(int argc, char **argv)
{
	pthread_t	*p;
	int			nb_p;
	int			i;

	if (argc < 5 || argc > 6)
	{
		printf("Usage : number_of_philosophers time_to_die time_to_eat"
			" time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}

	i = 1;
	while (i < argv[1])
	{
		if (pthread_create(p + i, NULL, &philo, NULL) != 0)
			return (2);
		i++;
	}
	i = 1;
	while (i < argv[1])
	{
		if (pthread_join(p[i], NULL) != 0)
			return (2);
		i++;
	}	
	return (0);
}

void	*philo()
{
	
}