/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:08:49 by emoreau           #+#    #+#             */
/*   Updated: 2023/09/27 23:00:09 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	die(t_philo *philo)
{
	if (philo->last_time_to_eat - ft_time() == 0)
		return (0);
	else
		return (1);
}

void eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	printf("philosophe %d n'a pas manger depuis %ld milliseconde\n", philo->num, ft_time() - philo->last_time_to_eat);
	printf("---%d---\n", philo->data->time_die);
	if (ft_time() - philo->last_time_to_eat > philo->data->time_die)
	{
		ft_print(philo, "is died");
		philo->data->death = 0;
		exit(1);
	}
	pthread_mutex_lock(philo->fork);
	ft_print(philo, "has taken a fork");
	pthread_mutex_lock(philo->next->fork);
	ft_print(philo, "has taken a fork");
	ft_print(philo, "is eating");
	pthread_mutex_unlock(&philo->data->print);
	usleep(philo->data->time_eat * 1000);
	philo->last_time_to_eat = ft_time();
	// printf("\033[31m philosophe : %d heure du dernier repas : %ld\n\033[0m",philo->num, philo->last_time_to_eat);
	pthread_mutex_unlock(philo->fork);
	pthread_mutex_unlock(philo->next->fork);
	// ft_sleep(data->time_eat, 1);
}

void	ft_spleep(t_philo *philo)
{
	ft_print(philo, "is sleeping");
	usleep(philo->data->time_sleep * 1000);
}


void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	// printf("\e[0;50mthread du philosophe %d\n", data->philo->num);
	if (philo->num % 2 == 0)
		usleep((philo->data->time_eat * 1000) / 2);
	// // while(die(data) == 0)
	// printf("nombre de tour a faire= %d\n", philo->data->win);
	if (philo->i == -1)
	{
		while(philo->data->death == 1)
		{
			// printf("thread du philosophe %d\n", data->philo->num);
			eat(philo);
			ft_spleep(philo);
			// ft_usleep(1000, 5);
			// break;
		}
	}
	else
	{
		while(philo->i != philo->data->win && philo->data->death == 1)
		{
	// printf("nombre de tour = %d\n", philo->i);
			// printf("thread du philosophe %d\n", data->philo->num);
			eat(philo);
			ft_spleep(philo);
			// ft_usleep(1000, 5);
			// break;
			philo->i++;
		}
	}
	return (philo);
}

int	main(int ac, char **av)
{
	int		i;
	t_philo	*philo;
	// t_data	*data;

	if (ac != 5 && ac != 6)
		return (printf("erreur arg\n"), 0);

	i = 0;

	philo = init(ac, av);
	// (void)data;
	// cree un thread pour chaque philosof
	// un philosophe sur 2 manges
	// les autres pensesou dorment
	// des qu'ils ont finis de manger les philosophe qui penses vont manger 
	// while (philo->num != philo->data->number)
	// {
	// 	printf("%d\n", philo->num);
	// 	philo = philo->next;
	// }
	// printf("time = %ld\n", philo->data->start);

	while (i < philo->data->number)
	{
		pthread_create(&philo->thread, NULL, &routine, (void *)philo);
		philo = philo->next;
		i++;
	}
	while (i != 0)
	{
		// printf("i = %d", i);
		pthread_join(philo->thread, NULL);
		philo = philo->next;
		i--;
	}


	return (0);
}