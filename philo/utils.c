/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 22:59:12 by jberredj          #+#    #+#             */
/*   Updated: 2022/01/15 15:30:29 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include "philosophers.h"

uint64_t	get_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

bool	is_running(t_philos *self)
{
	bool	state;

	pthread_mutex_lock(self->print_mt);
	state = *self->is_running;
	pthread_mutex_unlock(self->print_mt);
	return (state);
}

void	set_philo_times(t_philos *self, t_args args)
{
	self->time_die = args.time_die;
	self->time_eat = args.time_eat;
	self->time_sleep = args.time_sleep;
	self->must_eat = args.must_eat_nbr;
	self->nbr_philos = args.nbr_philos;
}

void	my_usleep(int time)
{
	uint64_t	delay;

	delay = get_ms() + time;
	while (get_ms() < delay)
		usleep(40);
}
