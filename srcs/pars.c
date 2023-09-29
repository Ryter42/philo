/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:48:40 by elias             #+#    #+#             */
/*   Updated: 2023/09/29 19:06:38 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	isdigit_philo(int c)
{
	if (c > 47 && c < 58)
		return (1);
	else
		return (0);
}


int	all_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (isdigit_philo(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	checknum(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (all_num(av[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	pars(char  **av)
{
	// if (atoi_philo(av[1]) == 1)
	// 	return (-1);
	if (checknum(av) == 0)
		return (-1);
	else
		return (1);
}
