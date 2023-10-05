/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 19:41:41 by emoreau           #+#    #+#             */
/*   Updated: 2023/10/03 16:10:11 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_lst(t_philo *philo)
{
	free(philo->fork);
}

void	philo_free(t_philo *philo, int i)
{
	t_philo	*tmp;

	while (philo->num != i)
	{
		free_lst(philo);
		tmp = philo->next;
		free(philo);
		philo = tmp;
	}
	free_lst(philo);
	free(philo);
}

void	ft_free(t_philo *philo)
{
	int	i;

	i = philo->data->number;
	if (philo->data)
		free(philo->data);
	if (philo)
		philo_free(philo, i);
}
