/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:08:49 by emoreau           #+#    #+#             */
/*   Updated: 2023/09/26 19:15:35 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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

t_data	*create_data(int ac, char **av, t_data *next, int i)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->thread = malloc(sizeof(pthread_t));
	if (!data->thread)
		return (NULL);
	pthread_mutex_init(&data->mutex, NULL);
	data->philo = i;
	data->number = atoi_philo(av[1]);
	data->time_die = atoi_philo(av[2]);
	data->time_eat = atoi_philo(av[3]);
	data->time_sleep = atoi_philo(av[4]);
	if (ac == 6)
		data->win = atoi_philo(av[5]);
	data->next = next;
	return (data);
}

void	lstadd_back_philo(t_data **lst, t_data *new)
{
	t_data	*last;

	last = *lst;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new;
}

t_data	*init(int ac, char **av)
{
	int i;
	t_data	*data;

	i = atoi_philo(av[1]);
	data = NULL;
	while (i > 0)
	{
		data = create_data(ac, av, data, i);
		i--;
	}
	lstadd_back_philo(&data, data);
	return (data);
}

void	ft_sleep(int time, int seconde)
{
	int	i;

	i = 0;
	while(i < seconde)
	{
		usleep(time * 1000);
		i++;
	}
}

int	die(t_data *data)
{
	(void)data;
	ft_sleep(1000, 5);
	return (1);
}

void	*routine(void *arg)
{
	t_data *data;
	
	data = (t_data *)arg;
	while(die(data) == 0)
	{
		pthread_mutex_lock(&data->mutex);
		pthread_mutex_lock(&data->next->mutex);
		// eat();
		pthread_mutex_unlock(&data->mutex);
		pthread_mutex_unlock(&data->next->mutex);
	}
	return (data);
}

int	main(int ac, char **av)
{
	// int	i;
	t_data	*data;

	if (ac != 5 && ac != 6)
		return (printf("erreur arg\n"), 0);
	// i = 0;
	data = init(ac, av);
	// (void)data;
	// cree un thread pour chaque philosof
	// un philosophe sur 2 manges
	// les autres pensesou dorment
	// des qu'ils ont finis de manger les philosophe qui penses vont manger 
	// while (data->philo != data->number)
	// {
	// 	printf("%d\n", data->philo);
	// 	data = data->next;
	// }
	// printf("%d\n", data->philo);
	// usleep(100000);
	// ft_sleep(500, 10);
	while (data->philo != data->number)
	{
		pthread_create(data->thread, NULL, &routine, (void *)data);
		data = data->next;
	}
	pthread_create(data->thread, NULL, &routine, (void *)data);


	return (0);
}