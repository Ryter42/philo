/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:08:49 by emoreau           #+#    #+#             */
/*   Updated: 2023/09/26 14:00:19 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// int	philo_atoi(const char *nb)
// {
// 	int		i;
// 	int		s;
// 	int		nbr;
// 	char	*n;

// 	n = (char *)nb;
// 	nbr = 0;
// 	s = 1;
// 	i = 0;
// 	while ((n[i] > 6 && n[i] < 14) || n[i] == 32)
// 		i++;
// 	if (nb[i] == '-' || nb[i] == '+')
// 	{
// 		if (nb[i] == '-')
// 			s = -s;
// 		i++;
// 	}
// 	while (nb[i] > 47 && nb[i] < 58)
// 	{
// 		nbr = nbr * 10 + nb[i] - 48;
// 		i++;
// 	}
// 	return (nbr * s);
// }


int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	// cree un thread pour chaque philosof
	// un philosophe sur 2 manges
	// les autres pensesou dorment
	// des qu'ils ont finis de manger les philosophe qui penses vont manger 
	// printf("🙆%d", 🙆‍♀️);
	// printf("🙆%d", 🙆‍♀️);
	printf("'g\342'\n");
	
	return (0);
}