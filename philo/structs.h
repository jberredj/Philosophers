/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 18:56:54 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/30 23:27:49 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include <stdint.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_args
{
	uint64_t	nbr_philos;
	uint64_t	time_die;
	uint64_t	time_eat;
	uint64_t	time_sleep;
	bool		must_eat;
	uint64_t	must_eat_nbr;
}				t_args;

typedef struct s_philo
{
	uint64_t		id;
	uint64_t		*time_begin;
	uint64_t		time_die;
	uint64_t		time_eat;
	uint64_t		time_sleep;
	uint64_t		must_eat;
	uint64_t		last_eat;
	uint64_t		has_eaten;
	pthread_mutex_t	monitor_mt;
	pthread_mutex_t	*satiated_mt;
	bool			*is_running;
	pthread_mutex_t	*print_mt;
	pthread_mutex_t	*forks[2];
	pthread_t		thread;
	bool			satiated;
	uint64_t		*notify_satiation;
}				t_philos;

typedef struct s_table
{
	uint64_t		nbr_philos;
	uint64_t		nbr_created;
	uint64_t		time_begin;
	uint64_t		must_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mt;
	pthread_mutex_t	satiated_mt;
	uint64_t		philos_satiated;
	bool			is_running;
	t_philos		*philos;
}				t_table;

#endif