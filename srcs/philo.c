/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:08:49 by emoreau           #+#    #+#             */
/*   Updated: 2023/09/29 18:52:53 by elias            ###   ########.fr       */
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
	// t_data	*data;

	if (ac != 5 && ac != 6)
		return (printf("erreur arg\n"), 0);

	i = 0;

	if (pars(av) < 0)
		return(printf("erreur arg\n"), 0);
	philo = init(ac, av);
	// (void)data;
	// cree un thread pour chaque philosof
	// un philosophe sur 2 manges
	// les autres pensesou dorment
	// des qu'ils ont finis de manger les philosophe qui penses vont manger 
	// while (philo->num != philo->data->number)
	// {
	// 	printf("%d\n", philo->num);
	// 	philo = philo->next;
	// }
	// printf("time = %ld\n", philo->data->start);
	if (philo->data->number == 1)
		return (one_philo(philo), ft_free(philo), 0);	
	
	while (i < philo->data->number)
	{
		pthread_create(&philo->thread, NULL, &routine, (void *)philo);
		philo = philo->next;
		i++;
		// usleep(1000);
	}
	while (i != 0)
	{
		// printf("i = %d\n", i);
		pthread_join(philo->thread, NULL);
		philo = philo->next;
		i--;
	}
	ft_free(philo);

	return (0);
}