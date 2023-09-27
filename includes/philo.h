/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:06:31 by emoreau           #+#    #+#             */
/*   Updated: 2023/09/27 16:58:40 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_philo
{
	int	num;
	pthread_t thread;
	pthread_mutex_t *fork;
	struct s_philo *next;
	struct s_data	*data;	

}	t_philo;

typedef struct s_data
{
	int	number;
	int time_die;
	int time_eat;
	int time_sleep;
	int win;
	pthread_mutex_t print;
	// struct s_philo *philo;

}	t_data;

t_data	*init(int ac, char **av);
t_philo	*chaine_philo(int i);
t_philo	*create_philo(t_philo *next, int i);
void	lstadd_back_philo(t_philo **lst, t_philo *new);
int		atoi_philo(const char *nb);

#endif