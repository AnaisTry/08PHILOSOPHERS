/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angassin <angassin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 17:27:34 by angassin          #+#    #+#             */
/*   Updated: 2023/05/27 20:55:34 by angassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*									[Includes]								*/

# include <pthread.h>
// printf
# include <stdio.h>
// malloc, free
# include <stdlib.h>
# include <limits.h>
// usleep
# include <unistd.h>

/*									[Macros]								*/

# define OK 0
# define CHILD 0

/*									[Utils]									*/

int	ft_atoi(const char *str);

#endif