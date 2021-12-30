/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 19:16:07 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/27 22:02:28 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>
#include "structs.h"
#include "philosophers.h"

static int	string_is_positive_nbr(char *str)
{
	if (*str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

static int	check_for_int_max(char *str)
{
	size_t	len;
	char	*int_max;
	int		val_cmp[2];

	int_max = "2147483647";
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			int_max = "2147483648";
		str++;
	}
	len = ft_strlen(str);
	if (len > 10)
		return (1);
	else if (len == 10)
	{
		while (*str)
		{
			val_cmp[0] = (int)(*str++ - '0');
			val_cmp[1] = (int)(*int_max++ - '0');
			if (val_cmp[0] > val_cmp[1])
				return (-1);
		}
	}
	return (0);
}

static int	get_arg_value(uint64_t *nbr, char *arg, uint64_t min_val)
{
	uint64_t	value;

	if (!string_is_positive_nbr(arg))
		return (1);
	if (check_for_int_max(arg))
		return (1);
	value = (uint64_t)ft_atoi(arg);
	if (value < min_val)
		return (1);
	*nbr = value;
	return (0);
}

int	parse_arg(int ac, char **av, t_args *args)
{
	ft_memset(args, 0, sizeof(t_args));
	if (ac < 5)
		return (1);
	if (ac > 6)
		return (2);
	if (get_arg_value(&args->nbr_philos, av[1], MIN_NBR_PHILO))
		return (3);
	if (get_arg_value(&args->time_die, av[2], MIN_TIME_DIE))
		return (4);
	if (get_arg_value(&args->time_eat, av[3], MIN_TIME_EAT))
		return (5);
	if (get_arg_value(&args->time_sleep, av[4], MIN_TIME_SLEEP))
		return (6);
	if (ac == 6)
	{
		args->must_eat = true;
		if (get_arg_value(&args->must_eat_nbr, av[5], MIN_EAT_NBR))
			return (7);
	}
	return (0);
}
