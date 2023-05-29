/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angassin <angassin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 17:30:28 by angassin          #+#    #+#             */
/*   Updated: 2023/05/29 07:57:20 by angassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo(void);
int		check_input(int argc, char **argv);

/*
	Program that creates threads that share mutual exclusion synchronization 
	primitives, a kind of locks
*/
int	main(int argc, char **argv)
{
	pthread_t	p[OPEN_MAX];
	void		*res;
	int			i;

	if (check_input(argc, argv) != OK)
		return (1);
	res = NULL;
	i = 1;
	while (i < ft_atoi(argv[1]) + 1)
	{
		if (pthread_create(p + i, NULL, &philo, NULL) != OK)
		{
			free(res);
			return (2);
		}		
		i++;
	}
	i = 1;
	while (i < ft_atoi(argv[1]) + 1)
	{
		if (pthread_join(p[i], &res) != OK)
		{
			free(res);
			return (2);
		}
		i++;
		free(res);
	}
	return (0);
}

void	*philo(void)
{
	int	*res;

	printf("Hello from threads\n");
	res = malloc(sizeof(*res));
	*res = 1;
	sleep(3);
	printf("Ending thread\n");
	return (res);
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
	i = 0;
	while (i < argc)
	{
		if (ft_atoi(argv[i]) <= 0)
			return (2);
		i++;
	}
	return (0);
}
