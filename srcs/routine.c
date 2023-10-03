/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:50:40 by elias             #+#    #+#             */
/*   Updated: 2023/10/01 19:35:37 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	take_fork(t_philo *philo)
{

	if (philo->num != philo->data->number)
	{
		pthread_mutex_lock(philo->fork);
		if (cheak_death(philo) == 0)
			return (0);
		is_death(philo);
		if (cheak_death(philo) == 0)
		{
			pthread_mutex_unlock(&philo->data->print);
			pthread_mutex_unlock(philo->fork);
			return (0);
		}
		pthread_mutex_lock(philo->next->fork);
		pthread_mutex_lock(&philo->data->print);
		ft_print(philo, "has taken a fork");

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
	philo->last_time_to_eat = ft_time();
	usleep(philo->data->time_eat * 1000);
	pthread_mutex_unlock(philo->fork);
	pthread_mutex_unlock(philo->next->fork);
	return (1);
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
	if (philo->num % 2 == 0)
		usleep((philo->data->time_eat * 1000) / 2);
	if (philo->i == -1)
	{
		while(cheak_death(philo) == 1)
		{
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
		}
	}
	else
	{
		while(philo->i != philo->data->win && cheak_death(philo) == 1)
		{
	
			if (eat(philo) == 0)
				return (NULL);
			if (cheak_death(philo) == 0)
				return (NULL);
			ft_sleep(philo);
			pthread_mutex_lock(&philo->data->print);
			ft_print(philo, " is thinking");
			pthread_mutex_unlock(&philo->data->print);
			philo->i++;
		}
	}
	return (philo);
}