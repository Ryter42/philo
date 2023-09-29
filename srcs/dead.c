/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:52:57 by elias             #+#    #+#             */
/*   Updated: 2023/09/29 18:53:06 by elias            ###   ########.fr       */
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

int	cheak_death(t_philo *philo)
{
	int i;
			pthread_mutex_lock(&philo->data->dead);
	i = philo->data->death;
			pthread_mutex_unlock(&philo->data->dead);
	return (i);
}