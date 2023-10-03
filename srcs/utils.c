/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 22:02:13 by elias             #+#    #+#             */
/*   Updated: 2023/10/01 19:35:53 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
 #include <string.h>

void	ft_usleep(int time, int seconde)
{
	int	i;

	i = 0;
	while(i < seconde)
	{
		usleep(time * 1000);
		i++;
	}
}

void	ft_print(t_philo *philo, char *str)
{
	if (cheak_death(philo) == 1 || strcmp(str, "died") == 0)
	{	
		printf("%ld	%d %s\n", ft_time() - philo->data->start, philo->num, str);
	}
}

long	ft_time(void)
{
	struct timeval	time;
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec * 0.001));
}

int	atoi_philo(const char *nb)
{
	int		i;
	int		s;
	int		nbr;
	char	*n;

	n = (char *)nb;
	nbr = 0;
	s = 1;
	i = 0;
	while ((n[i] > 6 && n[i] < 14) || n[i] == 32)
		i++;
	if (nb[i] == '-' || nb[i] == '+')
	{
		if (nb[i] == '-')
			s = -s;
		i++;
	}
	while (nb[i] > 47 && nb[i] < 58)
	{
		nbr = nbr * 10 + nb[i] - 48;
		i++;
	}
	return (nbr * s);
}
