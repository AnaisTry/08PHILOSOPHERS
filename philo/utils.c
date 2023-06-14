/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angassin <angassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 20:18:48 by angassin          #+#    #+#             */
/*   Updated: 2023/06/14 16:15:20 by angassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	unsigned long	nb;
	int				sign;

	nb = 0;
	sign = 1;
	while (*str && (*str == ' ' || (*str >= '\t' && *str <= '\r')))
		str++;
	while (*str == '-' || *str == '+')
	{
		if (*(str + 1) == '+' || *(str + 1) == '-')
			return (0);
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str && (*str >= '0' && *str <= '9'))
	{
		nb = nb * 10 + *str - '0';
		if (nb > LLONG_MAX && sign == 1)
			return (-1);
		if (nb > LLONG_MAX && sign == -1)
			return (0);
		str++;
	}
	return (nb * sign);
}

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

time_t	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

void	ft_usleep(time_t time)
{
	time_t	start;

	start = get_time();
	while (get_time() < start + time)
	{
		usleep(100);
	}
}

t_bool	is_dead(t_symposium *s)
{
	pthread_mutex_lock(s->death);
	if (s->dead)
	{
		pthread_mutex_unlock(s->death);
		return (TRUE);
	}
	pthread_mutex_unlock(s->death);
	return (FALSE);
}
