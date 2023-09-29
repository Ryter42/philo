/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:50:40 by elias             #+#    #+#             */
/*   Updated: 2023/09/29 19:48:33 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	take_fork(t_philo *philo)
{

	if (philo->num != philo->data->number)
	{
		pthread_mutex_lock(philo->fork);
		// printf("mutex %d lock\n", philo->num);
		// printf("%ld		dernier fois que philosophe %d a manger\n", philo->last_time_to_eat, philo->num);
		// printf("%ld		philosophe %d n'a pas manger depuis %ld milliseconde\n",ft_time(), philo->num, ft_time() - philo->last_time_to_eat);
		// printf("---%d---\n", philo->data->time_die);
		if (cheak_death(philo) == 0)
			return (0);
		// printf("%ld		philosophe %d n'a pas manger depuis %ld milliseconde\n",ft_time(), philo->num, ft_time() - philo->last_time_to_eat);
		is_death(philo);
		// printf("%d\n", philo->data->death);
		if (cheak_death(philo) == 0)
		{
			ft_print(philo, "died");
			// pthread_mutex_unlock(&philo->data->print);
			pthread_mutex_unlock(philo->fork);
	
			return (0);
		}
		pthread_mutex_lock(philo->next->fork);
		pthread_mutex_lock(&philo->data->print);
		ft_print(philo, "has taken a fork");
		// printf("mutex %d lock\n", philo->next->num);
		ft_print(philo, "has taken a fork");
		ft_print(philo, "is eating");
		pthread_mutex_unlock(&philo->data->print);
	}
	else
	{
		pthread_mutex_lock(philo->next->fork);
		is_death(philo);
		if (cheak_death(philo) == 0)
		{
			ft_print(philo, "died");
			pthread_mutex_unlock(philo->fork);
	
			return (0);
		}
		pthread_mutex_lock(philo->fork);
		pthread_mutex_lock(&philo->data->print);
		ft_print(philo, "has taken a fork");
		ft_print(philo, "has taken a fork");
		ft_print(philo, "is eating");
		pthread_mutex_unlock(&philo->data->print);
	}
	
	return (1);
}

int eat(t_philo *philo)
{
	if(take_fork(philo) == 0)
		return(0);
	usleep(philo->data->time_eat * 1000);
	philo->last_time_to_eat = ft_time();
	pthread_mutex_unlock(philo->fork);
	// printf("mutex %d unlock\n", philo->num);
	pthread_mutex_unlock(philo->next->fork);
	// printf("mutex %d unlock\n", philo->next->num);
	return (1);
	// printf("\033[31m %ld	%d a pauser sa fourchette\n\033[0m", ft_time(), philo->num);
	// ft_sleep(data->time_eat, 1);
}

void	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	ft_print(philo, "is sleeping");
	pthread_mutex_unlock(&philo->data->print);
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
		while(cheak_death(philo) == 1)
		{
			// printf("thread du philosophe %d\n", data->philo->num);
			if (eat(philo) == 0)
				return (NULL);
			if (cheak_death(philo) == 0)
				return (NULL);
			ft_sleep(philo);
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
			ft_sleep(philo);
			pthread_mutex_lock(&philo->data->print);
			ft_print(philo, " is thinking");
			pthread_mutex_unlock(&philo->data->print);
			// break;
			philo->i++;
		}
	}
	return (philo);
}