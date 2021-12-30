/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 21:45:10 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/30 23:23:35 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "structs.h"
#include "philosophers.h"

static int	fail_malloc_forks(void)
{
	ft_putstr_fd("Error: Failed malloc() forks\n", 2);
	return (1);
}

void	free_table(t_table *table)
{
	int	i;

	i = -1;
	if (table->forks)
		while (++i < (int)table->nbr_philos)
			pthread_mutex_destroy(&table->forks[i]);
	if (table->forks)
		free(table->forks);
	pthread_mutex_destroy(&table->print_mt);
	pthread_mutex_destroy(&table->satiated_mt);
	if (table->philos)
		free(table->philos);
}

int	init_table(t_table *table, uint64_t nbr_philos)
{
	int	i;

	ft_memset(table, 0, sizeof(t_table));
	table->nbr_philos = nbr_philos;
	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* nbr_philos);
	if (!table->forks)
		return (fail_malloc_forks());
	i = -1;
	while (++i < (int)table->nbr_philos)
		pthread_mutex_init(&table->forks[i], NULL);
	pthread_mutex_init(&table->print_mt, NULL);
	pthread_mutex_init(&table->satiated_mt, NULL);
	table->is_running = true;
	return (0);
}
