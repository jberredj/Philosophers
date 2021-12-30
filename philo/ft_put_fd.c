/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 19:07:57 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/27 22:23:25 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

static void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (*s++)
		i++;
	return (i);
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	us_n;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		us_n = (unsigned int)n;
		us_n = -us_n;
	}
	else
		us_n = (unsigned int)(n);
	if (us_n >= 10)
	{
		ft_putnbr_fd(us_n / 10, fd);
	}
	ft_putchar_fd((char)(us_n % 10 + '0'), fd);
}

void	ft_put_unbr_fd(unsigned int n, int fd)
{
	if (n >= 10)
		ft_putnbr_fd(n / 10, fd);
	ft_putchar_fd((char)(n % 10 + '0'), fd);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s != NULL)
		write(fd, s, ft_strlen(s));
}
