/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angassin <angassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 20:18:48 by angassin          #+#    #+#             */
/*   Updated: 2023/06/09 12:40:42 by angassin         ###   ########.fr       */
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

int	error_exit(t_symposium *s, char *message)
{
	free(s->philos);
	free(s->forks);
	free(s->death);
	perror(message);
	return (-1);
}

time_t	get_time(t_symposium *s)
{
	struct timeval	current_time;
	time_t			time_in_milliseconds;

	if (gettimeofday(&current_time, NULL) != OK)
		return (error_exit(s, "Could not get current time"));
	time_in_milliseconds = current_time.tv_sec * 1000
		+ current_time.tv_usec / 1000;
	return (time_in_milliseconds);
}

void	ft_usleep(time_t time)
{
	time_t	start = get_time(NULL);

	while (get_time(NULL) < start + time)
	{
		usleep(100);
	}
}
