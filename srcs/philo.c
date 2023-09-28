/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:08:49 by emoreau           #+#    #+#             */
/*   Updated: 2023/09/28 21:30:56 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	is_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead);
	if (ft_time() - philo->last_time_to_eat > philo->data->time_die)
		philo->data->death = 0;
	pthread_mutex_unlock(&philo->data->dead);
}

int	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	pthread_mutex_lock(philo->fork);
	// printf("%ld		dernier fois que philosophe %d a manger\n", philo->last_time_to_eat, philo->num);
	// printf("%ld		philosophe %d n'a pas manger depuis %ld milliseconde\n",ft_time(), philo->num, ft_time() - philo->last_time_to_eat);
	// printf("---%d---\n", philo->data->time_die);
	is_death(philo);
	// printf("%d\n", philo->data->death);
	if (cheak_death(philo) == 0)
	{
		ft_print(philo, "died");
		pthread_mutex_unlock(&philo->data->print);
		pthread_mutex_unlock(philo->fork);

		return (0);
	}
	ft_print(philo, "has taken a fork");
	pthread_mutex_lock(philo->next->fork);
	ft_print(philo, "has taken a fork");
	ft_print(philo, "is eating");
	pthread_mutex_unlock(&philo->data->print);
	return (1);
}

int eat(t_philo *philo)
{
	if(take_fork(philo) == 0)
		return(0);
	philo->last_time_to_eat = ft_time();
	usleep(philo->data->time_eat * 1000);
	pthread_mutex_unlock(philo->fork);
	pthread_mutex_unlock(philo->next->fork);
	return (1);
	// printf("\033[31m %ld	%d a pauser sa fourchette\n\033[0m", ft_time(), philo->num);
	// ft_sleep(data->time_eat, 1);
}

void	ft_spleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	ft_print(philo, "is sleeping");
	pthread_mutex_unlock(&philo->data->print);
	usleep(philo->data->time_sleep * 1000);
}

int	cheak_death(t_philo *philo)
{
	int i;
			pthread_mutex_lock(&philo->data->dead);
	i = philo->data->death;
			pthread_mutex_unlock(&philo->data->dead);
	return (i);
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
		while(cheak_death(philo) == 1)
		{
			// printf("thread du philosophe %d\n", data->philo->num);
			if (eat(philo) == 0)
				return (NULL);
			if (cheak_death(philo) == 0)
				return (NULL);
			ft_spleep(philo);
			if (cheak_death(philo) == 0)
				return (NULL);			
			pthread_mutex_lock(&philo->data->print);
			ft_print(philo, " is thinking");
			pthread_mutex_unlock(&philo->data->print);
			// ft_usleep(1000, 5);
			// break;
		}
	}
	else
	{
		while(philo->i != philo->data->win && cheak_death(philo) == 1)
		{
	// printf("nombre de tour = %d\n", philo->i);
			// printf("thread du philosophe %d\n", data->philo->num);
			if (eat(philo) == 0)
				return (NULL);
			if (cheak_death(philo) == 0)
				return (NULL);
			ft_spleep(philo);
			pthread_mutex_lock(&philo->data->print);
			ft_print(philo, " is thinking");
			pthread_mutex_unlock(&philo->data->print);
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
		// printf("i = %d\n", i);
		pthread_join(philo->thread, NULL);
		philo = philo->next;
		i--;
	}
	ft_free(philo);

	return (0);
}