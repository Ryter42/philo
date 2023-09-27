/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:08:49 by emoreau           #+#    #+#             */
/*   Updated: 2023/09/27 17:23:45 by elias            ###   ########.fr       */
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

void eat(t_philo *philo)
{
	pthread_mutex_lock(philo->data->print);
	pthread_mutex_lock(philo->fork);
	printf("philosophe %d has taken a fork\n", philo->num);
	pthread_mutex_lock(philo->next->fork);
	printf("philosophe %d has taken a fork\n", philo->num);
	printf("philosophe %d is eating\n", philo->num);

	pthread_mutex_unlock(philo->data->print);
	usleep(philo->data->time_eat * 1000);
	pthread_mutex_unlock(philo->fork);
	pthread_mutex_unlock(philo->next->fork);
	// ft_sleep(data->time_eat, 1);
}

void	ft_spleep(t_philo *philo)
{
	printf("philosophe %d is sleeping\n", philo->num);
	usleep(philo->data->time_sleep * 1000);

	// ft_usleep(data->time_sleep);
}

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	// printf("\e[0;50mthread du philosophe %d\n", data->philo->num);
	if (philo->num % 2 == 0)
		usleep((philo->data->time_eat * 1000) / 2);
	// printf("die = %d\n", die(data));
	// // while(die(data) == 0)
	while(1)
	{
		// printf("thread du philosophe %d\n", data->philo->num);
		eat(philo);
		ft_spleep(philo);
		// ft_usleep(1000, 5);
		// break;
	}
	return (philo);
}

int	main(int ac, char **av)
{
	int	i;
	t_philo	*philo;
	t_data	*data;

	if (ac != 5 && ac != 6)
		return (printf("erreur arg\n"), 0);
	i = 0;

	philo = chaine_philo(atoi_philo(av[1]));
	data = init(ac, av);
	while (i < data->number)
	{
		philo->data = data;
		philo = philo->next;
		i++;
	}
	i = 0;
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

	while (i < philo->data->number)
	{
		pthread_create(&philo->thread, NULL, &routine, (void *)philo);
		philo = philo->next;
		i++;
	}
	while (i != 0)
	{
		pthread_join(philo->thread, NULL);
		philo = philo->next;
		i++;
	}


	return (0);
}