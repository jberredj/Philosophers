/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 23:01:20 by jberredj          #+#    #+#             */
/*   Updated: 2022/01/08 21:06:11 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>
#include "philosophers.h"
#include <unistd.h>

void	log_philo(t_philos *self, char *str, bool allready_locked)
{
	uint64_t	time;

	if (!allready_locked)
		pthread_mutex_lock(self->print_mt);
	if (*self->is_running)
	{
		ft_putstr_fd("[", 1);
		time = get_ms();
		ft_put_unbr_fd(time - *self->time_begin, 1);
		ft_putstr_fd(" ms] philo ", 1);
		ft_putnbr_fd(self->id, 1);
		ft_putstr_fd(str, 1);
	}
	if (!allready_locked)
		pthread_mutex_unlock(self->print_mt);
}

static void	eat(t_philos *self)
{
	pthread_mutex_lock(self->forks[0]);
	log_philo(self, TAKE_FORK, false);
	pthread_mutex_lock(self->forks[1]);
	log_philo(self, TAKE_FORK, false);
	pthread_mutex_lock(&self->monitor_mt);
	self->last_eat = get_ms();
	self->has_eaten++;
	pthread_mutex_unlock(&self->monitor_mt);
	log_philo(self, IS_EATING, false);
	usleep(self->time_eat * 1000);
	pthread_mutex_unlock(self->forks[0]);
	pthread_mutex_unlock(self->forks[1]);
}

static void	check_satiated(t_philos *self)
{
	uint64_t	must_eat;
	uint64_t	has_eaten;

	pthread_mutex_lock(&self->monitor_mt);
	must_eat = self->must_eat;
	has_eaten = self->has_eaten;
	pthread_mutex_unlock(&self->monitor_mt);
	if (must_eat && has_eaten >= must_eat && !self->satiated)
	{
		pthread_mutex_lock(self->satiated_mt);
		(*self->notify_satiation)++;
		self->satiated = true;
		pthread_mutex_unlock(self->satiated_mt);
	}
}

void	*philoshoper(void *arg)
{
	t_philos	*self;

	self = (t_philos *)arg;
	while (is_running(self))
	{
		eat(self);
		log_philo(self, IS_SLEEPING, false);
		usleep(self->time_sleep * 1000);
		log_philo(self, IS_THINKING, false);
		check_satiated(self);
	}
	return (NULL);
}
