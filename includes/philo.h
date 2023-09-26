/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:06:31 by emoreau           #+#    #+#             */
/*   Updated: 2023/09/26 18:49:17 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_data
{
	int	philo;
	int	number;
	int time_die;
	int time_eat;
	int time_sleep;
	int win;
	pthread_t *thread;
	pthread_mutex_t mutex;
	struct s_data *next;
}	t_data;

int	atoi_philo(const char *nb);

#endif