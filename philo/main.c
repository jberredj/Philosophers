/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 19:06:43 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/30 23:44:33 by jberredj         ###   ########.fr       */
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

static int	check_satiated(t_table *table)
{
	int	satiated;

	if (!table->must_eat)
		return (0);
	satiated = 0;
	pthread_mutex_lock(&table->satiated_mt);
	if (table->philos_satiated == table->nbr_philos)
		satiated = 1;
	pthread_mutex_unlock(&table->satiated_mt);
	if (satiated)
	{
		ft_putstr_fd("All philosophers are satiated\n", 1);
		table->is_running = false;
	}
	return (satiated);
}

void	monitor_philos(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&table->print_mt);
	while (table->is_running && !check_satiated(table))
	{
		pthread_mutex_unlock(&table->print_mt);
		usleep(1000);
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
