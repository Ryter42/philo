/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:02:34 by elias             #+#    #+#             */
/*   Updated: 2023/09/27 17:26:18 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philo.h"

int	atoi_philo(const char *nb)
{
	int		i;
	int		s;
	int		nbr;
	char	*n;

	n = (char *)nb;
	nbr = 0;
	s = 1;
	i = 0;
	while ((n[i] > 6 && n[i] < 14) || n[i] == 32)
		i++;
	if (nb[i] == '-' || nb[i] == '+')
	{
		if (nb[i] == '-')
			s = -s;
		i++;
	}
	while (nb[i] > 47 && nb[i] < 58)
	{
		nbr = nbr * 10 + nb[i] - 48;
		i++;
	}
	return (nbr * s);
}

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
	philo->thread = (pthread_t)malloc(sizeof(pthread_t));
	if (!philo->thread)
		return (NULL);
	philo->fork = malloc(sizeof(pthread_mutex_t));
	if (!philo->thread)
		return (NULL);
	pthread_mutex_init(philo->fork, NULL);
	philo->num = i;
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

t_data	*init(int ac, char **av)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	pthread_mutex_init(data->print, NULL);
	data->time_eat = atoi_philo(av[3]);
	data->number = atoi_philo(av[1]);
	data->time_die = atoi_philo(av[2]);
	data->time_sleep = atoi_philo(av[4]);
	if (ac == 6)
		data->win = atoi_philo(av[5]);
	return (data);
}