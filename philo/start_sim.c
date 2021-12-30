/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_sim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 23:04:04 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/30 23:28:27 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>
#include "philosophers.h"

static int	get_fork_id(int fork_nbr, int nbr_philos)
{
	if (fork_nbr >= nbr_philos)
		return (nbr_philos - fork_nbr);
	return (fork_nbr);
}

static void	attribute_forks(pthread_mutex_t *table_forks,
	pthread_mutex_t *philo_forks[2], int nbr_philos, int id)
{
	philo_forks[id % 2] = &table_forks[get_fork_id(id, nbr_philos)];
	philo_forks[((id % 2) + 1) % 2]
		= &table_forks[get_fork_id(id + 1, nbr_philos)];
}

static int	init_philos(t_args args, t_table *table)
{
	int	i;

	table->philos = (t_philos *)malloc(sizeof(t_philos) * args.nbr_philos);
	if (!table->philos)
	{
		ft_putstr_fd("Error: failed malloc() philos\n", 2);
		free_table(table);
		return (1);
	}
	i = -1;
	while (++i < (int)args.nbr_philos)
	{
		ft_memset(&table->philos[i], 0, sizeof(t_philos));
		table->philos[i].id = i + 1;
		set_philo_times(&table->philos[i], args);
		table->philos[i].satiated_mt = &table->satiated_mt;
		table->philos[i].notify_satiation = &table->philos_satiated;
		table->philos[i].is_running = &table->is_running;
		table->philos[i].print_mt = &table->print_mt;
		table->philos[i].time_begin = &table->time_begin;
		pthread_mutex_init(&table->philos[i].monitor_mt, NULL);
		attribute_forks(table->forks, table->philos[i].forks, args.nbr_philos,
			table->philos[i].id - 1);
	}
	return (0);
}

static int	launch_philos(t_table *table)
{
	int	i;

	i = -1;
	table->time_begin = get_ms();
	while (++i < (int)table->nbr_philos)
	{
		table->philos[i].last_eat = table->time_begin;
		table->philos[i].time_begin = &table->time_begin;
		if (pthread_create(&table->philos[i].thread, NULL, philoshoper,
				&table->philos[i]))
		{
			pthread_mutex_lock(&table->print_mt);
			table->is_running = false;
			pthread_mutex_unlock(&table->print_mt);
			return (1);
		}
		table->nbr_created = i + 1;
	}
	return (0);
}

int	prepare_meal(t_args args, t_table *table)
{
	if (init_table(table, args.nbr_philos))
		return (1);
	table->must_eat = args.must_eat_nbr;
	if (init_philos(args, table))
	{
		free_table(table);
		return (1);
	}
	if (launch_philos(table))
	{
		join_philos(table);
		free_table(table);
		return (1);
	}
	return (0);
}
