/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:52:57 by elias             #+#    #+#             */
/*   Updated: 2023/10/05 20:22:17 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	is_death(t_philo *philo)
{
	// pthread_mutex_lock(&philo->data->dead);
	if (ft_time() - philo->last_time_to_eat >= philo->data->time_die + 10)
		philo->data->death = 0;
	// pthread_mutex_unlock(&philo->data->dead);
}

int	check_death(t_philo *philo)
{
	int	i;

	pthread_mutex_lock(&philo->data->dead);
	i = philo->data->death;
	pthread_mutex_unlock(&philo->data->dead);
	return (i);
}

int	death(t_philo *philo)
{
	int	i;
	
	pthread_mutex_lock(&philo->data->dead);
	is_death(philo);
	i = philo->data->death;
	if (i == 0 && philo->data->see_dead == 1)
	{
		printf("%ld	%d died\n", ft_time() - philo->data->start, philo->num);
		// ft_print(philo, "died");
		philo->data->see_dead = 0;
	}
	pthread_mutex_unlock(&philo->data->dead);
	return (i);
}
