/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:08:49 by emoreau           #+#    #+#             */
/*   Updated: 2023/09/26 17:10:53 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	philo_atoi(const char *nb)
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

t_data	*init(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	data->philosophe = philo_atoi(av[1]);
	data->time_die = philo_atoi(av[2]);
	data->time_eat = philo_atoi(av[3]);
	data->time_sleep = philo_atoi(av[4]);
	if (ac == 6)
		data->win = philo_atoi(av[5]);
	return (data);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = init(ac, av);
	// cree un thread pour chaque philosof
	// un philosophe sur 2 manges
	// les autres pensesou dorment
	// des qu'ils ont finis de manger les philosophe qui penses vont manger 

	printf("'%d\n", data->philosophe);
	printf("'%d\n", data->time_die);
	printf("'%d\n", data->time_eat);
	printf("'%d\n", data->time_sleep);
	
	return (0);
}