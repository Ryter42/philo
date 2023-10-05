/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:26:32 by emoreau           #+#    #+#             */
/*   Updated: 2023/10/05 18:42:12 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	loop_b(t_philo *philo)
{
	while (philo->i != philo->data->win && cheak_death(philo) == 1)
	{
		if (eat(philo) == 0)
			return ;
		philo->i++;
		if (philo->i == philo->data->win)
		{
			break ;
		}
		if (cheak_death(philo) == 0)
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
	while (i < b)
	{
		// printf("%d\n", cheak_death(philo));
		usleep(1000);
		if (cheak_death(philo) == 0)
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
	// while (i < philo->data->time_sleep)
	// {
	// 	// printf("%d\n", cheak_death(philo));
	// 	usleep(1000);
	// 	if (cheak_death(philo) == 0)
	// 		return ;
	// 	i++;
	// }
	// printf("tooto\n");
}
