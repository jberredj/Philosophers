/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 19:44:13 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/27 20:09:06 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philosophers.h"

static int	error_nbr_args(int code)
{
	if (code == 1)
		ft_putstr_fd("Not enough arguments.\n", 2);
	if (code == 2)
		ft_putstr_fd("Too many arguments.\n", 2);
	ft_putstr_fd("Usage: ./philo number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]\n", 2);
	return (1);
}

int	error_args(int code)
{
	if (code)
	{
		write(2, "Error: ", 7);
		if (code <= 2)
			return (error_nbr_args(code));
		if (code > 2)
			ft_putstr_fd("Invalid argument for \"", 2);
		if (code == 3)
			ft_putstr_fd("number_of_philosophers\"\n", 2);
		if (code == 4)
			ft_putstr_fd("time_to_die\"\n", 2);
		if (code == 5)
			ft_putstr_fd("time_to_eat\"\n", 2);
		if (code == 6)
			ft_putstr_fd("time_to_sleep\"\n", 2);
		if (code == 7)
			ft_putstr_fd("number_of_times_each_philosopher_must_eat\"\n", 2);
		return (1);
	}
	return (0);
}
