/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:02:34 by elias             #+#    #+#             */
/*   Updated: 2023/10/01 19:28:29 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philo.h"

void	lstadd_back_philo(t_philo **lst, t_philo *new)
{
	t_philo	*last;

	last = *lst;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new;
}

t_philo	*create_philo(t_philo *next, int i)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->fork = malloc(sizeof(pthread_mutex_t));
	if (!philo->fork)
		return (NULL);
	pthread_mutex_init(philo->fork, NULL);
	philo->num = i;
	philo->i = 0;
	philo->last_time_to_eat = ft_time();
	philo->next = next;
	return (philo);
}

t_philo	*chaine_philo(int i)
{
	t_philo	*philo;

	philo = NULL;
	while (i > 0)
	{
		philo = create_philo(philo, i);
		i--;
	}
	lstadd_back_philo(&philo, philo);
	return (philo);
}

t_data	*create_data(int ac, char **av)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->dead, NULL);
	data->time_eat = atoi_philo(av[3]);
	data->number = atoi_philo(av[1]);
	data->time_die = atoi_philo(av[2]);
	data->time_sleep = atoi_philo(av[4]);
	if (ac == 6)
		data->win = atoi_philo(av[5]);
	else
		data->win = -1;
	data->start = ft_time();
	data->death = 1;
	return (data);
}

t_philo	*init(int ac, char **av)
{
	t_data *data;
	t_philo *philo;
	int		i;

	philo = chaine_philo(atoi_philo(av[1]));
	data = create_data(ac, av);
	i = 0;
	while (i < data->number)
	{
		philo->data = data;
		philo = philo->next;
		i++;
	}
	return (philo);
}