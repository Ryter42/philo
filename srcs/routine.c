/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:50:40 by elias             #+#    #+#             */
/*   Updated: 2023/10/05 20:19:26 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	last_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->next->fork);
	// is_death(philo);
	if (death(philo) == 0)
	{
		// ft_print(philo, "died");
		pthread_mutex_unlock(philo->next->fork);
		return (0);
	}
	pthread_mutex_lock(philo->fork);
	pthread_mutex_lock(&philo->data->print);
	ft_print(philo, "has taken a fork");
	ft_print(philo, "has taken a fork");
	ft_print(philo, "is eating");
	pthread_mutex_unlock(&philo->data->print);
	return (1);
}

int	take_fork(t_philo *philo)
{
	// if (philo->num != philo->data->number)
	if (philo->num % 2 == 1)
	{
		pthread_mutex_lock(philo->fork);
		if (death(philo) == 0)
			return (0);
		// is_death(philo);
		if (death(philo) == 0)
		{
			// ft_print(philo, "died");
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
		if (last_fork(philo) == 0)
			return (0);
	}
	return (1);
}

void	loop_a(t_philo *philo)
{
	while (death(philo) == 1)
	{
		if (eat(philo) == 0)
			return ;
		if (death(philo) == 0)
			return ;
		ft_sleep(philo);
		if (death(philo) == 0)
			return ;
		pthread_mutex_lock(&philo->data->print);
		ft_print(philo, " is thinking");
		pthread_mutex_unlock(&philo->data->print);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	// if (philo->num % 2 == 0)
		// usleep_loop(philo, (philo->data->time_eat * 1000) / 2);
		// usleep((philo->data->time_eat * 1000)/ 2);
	if (philo->i == -1)
		loop_a(philo);
	else
		loop_b(philo);
	return (philo);
}
