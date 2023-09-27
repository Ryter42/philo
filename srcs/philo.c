/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:08:49 by emoreau           #+#    #+#             */
/*   Updated: 2023/09/27 16:32:34 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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

int	die(t_data *data)
{
	(void)data;
	ft_usleep(1000, 10);
	return (1);
}

void eat(t_data *data)
{
	pthread_mutex_lock(&data->philo->fork);
	printf("philosophe %d has taken a fork\n", data->philo->num);
	pthread_mutex_lock(&data->philo->next->fork);
	printf("philosophe %d has taken a fork\n", data->philo->num);
	printf("philosophe %d is eating\n", data->philo->num);
	usleep(data->time_eat * 1000);
	pthread_mutex_unlock(&data->philo->fork);
	pthread_mutex_unlock(&data->philo->next->fork);
	// ft_sleep(data->time_eat, 1);
}

void	ft_spleep(t_data *data)
{
	printf("philosophe %d is sleeping\n", data->philo->num);
	usleep(data->time_sleep * 1000);

	// ft_usleep(data->time_sleep);
}

void	*routine(void *arg)
{
	t_data *data;

	data = (t_data *)arg;
	printf("\e[0;50mthread du philosophe %d\n", data->philo->num);
	if (data->philo->num % 2 == 0)
		usleep((data->time_eat * 1000) / 2);
	// printf("die = %d\n", die(data));
	// // while(die(data) == 0)
	while(1)
	{
		// printf("thread du philosophe %d\n", data->philo->num);
		eat(data);
		ft_spleep(data);
		// ft_usleep(1000, 5);
		// break;
	}
	return (data);
}

int	main(int ac, char **av)
{
	int	i;
	t_data	*data;

	if (ac != 5 && ac != 6)
		return (printf("erreur arg\n"), 0);
	i = 0;

	data = init(ac, av);
	// (void)data;
	// cree un thread pour chaque philosof
	// un philosophe sur 2 manges
	// les autres pensesou dorment
	// des qu'ils ont finis de manger les philosophe qui penses vont manger 
	// while (data->philo->num != data->number)
	// {
	// 	printf("%d\n", data->philo->num);
	// 	data->philo = data->philo->next;
	// }
	printf("%d\n", data->philo->num);

	while (i < data->number)
	{
		printf("\e[0;31mthread %d crée\n", data->philo->num);
		pthread_create(&data->philo->thread, NULL, &routine, (void *)data);
		// fflush(stdout);
		// printf("thread du philosophe %d\n", data->philo->num);
		data->philo = data->philo->next;
		i++;
	}
	// pthread_create(&data->philo->thread, NULL, &routine, (void *)data);
	data->philo = data->philo->next;
	while (i != 0)
	{
		pthread_join(data->philo->thread, NULL);
		data->philo = data->philo->next;
		i++;
	}


	return (0);
}