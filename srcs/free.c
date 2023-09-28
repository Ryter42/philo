/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 19:41:41 by emoreau           #+#    #+#             */
/*   Updated: 2023/09/28 20:30:04 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_lst(t_philo *philo)
{
	// free(philo->thread);
	free(philo->fork);
}

void	philo_free(t_philo *philo, int i)
{
	t_philo *tmp;

	// tmp = philo->next;
	// free_lst(philo);
	// while (philo)
		// printf("philo %d sur %d\n", philo->num, i);
	while (philo->num != i)
	{
		// printf("philo free %d\n", philo->num);
		free_lst(philo);
		tmp = philo->next;
		free(philo);
		philo = tmp;
	}
	free_lst(philo);
	free(philo);
}

void 	ft_free(t_philo *philo)
{
	int	i;

	i = philo->data->number;
	if (philo->data)
		free(philo->data);
	if (philo)
		philo_free(philo, i);
}