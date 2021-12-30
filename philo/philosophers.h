/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 19:23:33 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/30 23:15:16 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdlib.h>
# include "structs.h"
# define MIN_NBR_PHILO 1
# define MIN_TIME_DIE 1
# define MIN_TIME_EAT 1
# define MIN_TIME_SLEEP 1
# define MIN_EAT_NBR 1
# define TAKE_FORK " has taken a fork\n"
# define IS_EATING " is eating\n"
# define IS_SLEEPING " is sleeping\n"
# define IS_THINKING " is thinking\n"
# define DIED " died\n"

int			ft_atoi(const char *str);
int			ft_isdigit(int c);
void		*ft_memset(void *s, int c, size_t n);
int			parse_arg(int ac, char **av, t_args *args);
int			error_args(int code);
size_t		ft_strlen(const char *s);
void		ft_putnbr_fd(int n, int fd);
void		ft_put_unbr_fd(unsigned int n, int fd);
void		ft_putstr_fd(char *s, int fd);
void		free_table(t_table *table);
int			init_table(t_table *table, uint64_t nbr_philos);
uint64_t	get_ms(void);
void		log_philo(t_philos *self, char *str, bool allready_locked);
int			prepare_meal(t_args args, t_table *table);
void		join_philos(t_table *table);
bool		is_running(t_philos *self);
void		set_philo_times(t_philos *self, t_args args);
void		*philoshoper(void *arg);
#endif