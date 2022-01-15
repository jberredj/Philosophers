/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 19:06:43 by jberredj          #+#    #+#             */
/*   Updated: 2022/01/15 16:13:57 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <pthread.h>
#include "structs.h"
#include "philosophers.h"
#include <stdio.h>
#include <sys/time.h>

void	join_philos(t_table *table)
{
	int	i;

	i = -1;
	while (++i < (int)table->nbr_created)
		pthread_join(table->philos[i].thread, NULL);
}

void	monitor_philos(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&table->print_mt);
	while (table->is_running)
	{
		pthread_mutex_unlock(&table->print_mt);
		my_usleep(1);
		pthread_mutex_lock(&table->philos[i].monitor_mt);
		if (get_ms() - table->philos[i].last_eat > table->philos[i].time_die)
		{
			pthread_mutex_lock(&table->print_mt);
			log_philo(&table->philos[i], DIED, true);
			table->is_running = false;
			pthread_mutex_unlock(&table->print_mt);
		}
		pthread_mutex_unlock(&table->philos[i].monitor_mt);
		i++;
		if (i == (int)table->nbr_philos)
			i = 0;
		pthread_mutex_lock(&table->print_mt);
	}
	pthread_mutex_unlock(&table->print_mt);
}

int	main(int ac, char **av)
{
	t_args	args;
	t_table	table;

	if (error_args(parse_arg(ac, av, &args)))
		return (1);
	if (prepare_meal(args, &table))
		return (1);
	monitor_philos(&table);
	join_philos(&table);
	free_table(&table);
	return (0);
}
