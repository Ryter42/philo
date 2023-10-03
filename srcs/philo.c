/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:08:49 by emoreau           #+#    #+#             */
/*   Updated: 2023/10/01 19:26:05 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	one_philo(t_philo *philo)
{
	ft_print(philo, "take a fork");
	usleep(philo->data->time_die * 1000); 
	ft_print(philo, "died");
}

int	main(int ac, char **av)
{
	int		i;
	t_philo	*philo;

	if (ac != 5 && ac != 6)
		return (printf("erreur arg\n"), 0);
	i = 0;
	if (pars(av) < 0)
		return(printf("erreur arg\n"), 0);
	philo = init(ac, av);
	if (philo->data->number == 1)
		return (one_philo(philo), ft_free(philo), 0);	
	while (i < philo->data->number)
	{
		pthread_create(&philo->thread, NULL, &routine, (void *)philo);
		philo = philo->next;
		i++;
	}
	while (i != 0)
	{
		pthread_join(philo->thread, NULL);
		philo = philo->next;
		i--;
	}
	ft_free(philo);
	return (0);
}