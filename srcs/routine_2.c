/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:26:32 by emoreau           #+#    #+#             */
/*   Updated: 2023/10/05 20:21:41 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	loop_b(t_philo *philo)
{
	while (philo->i != philo->data->win && death(philo) == 1)
	{
		if (eat(philo) == 0)
			return ;
		philo->i++;
		if (philo->i == philo->data->win)
		{
			break ;
		}
		if (death(philo) == 0)
			return ;
		ft_sleep(philo);
		pthread_mutex_lock(&philo->data->print);
		ft_print(philo, " is thinking");
		pthread_mutex_unlock(&philo->data->print);
	}
}

void usleep_loop(t_philo *philo, int b)
{
	int	i;

	i = 0;
	while (i < b / 10)
	{
		// printf("%d\n", death(philo));
		usleep(1000 * 10);
		if (check_death(philo) == 0)
			return ;
		i++;
	}
}

int	eat(t_philo *philo)
{
	if (take_fork(philo) == 0)
		return (0);
	philo->last_time_to_eat = ft_time();
	// usleep(philo->data->time_eat * 1000);
	usleep_loop(philo, philo->data->time_eat);
	pthread_mutex_unlock(philo->fork);
	pthread_mutex_unlock(philo->next->fork);
	return (1);
}

void	ft_sleep(t_philo *philo)
{
	// int	i;

	// i = 0;
	pthread_mutex_lock(&philo->data->print);
	ft_print(philo, "is sleeping");
	pthread_mutex_unlock(&philo->data->print);
	usleep_loop(philo, philo->data->time_sleep);
	// usleep(1000 * philo->data->time_sleep);
	// while (i < philo->data->time_sleep)
	// {
	// 	// printf("%d\n", death(philo));
	// 	usleep(1000);
	// 	if (death(philo) == 0)
	// 		return ;
	// 	i++;
	// }
	// printf("tooto\n");
}
