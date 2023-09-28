/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:06:31 by emoreau           #+#    #+#             */
/*   Updated: 2023/09/27 22:41:38 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int	num;
	int	i;
	long last_time_to_eat;
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
	long start;
	int	death;
	pthread_mutex_t print;
	// struct s_philo *philo;

}	t_data;

t_philo	*init(int ac, char **av);
t_philo	*chaine_philo(int i);
t_philo	*create_philo(t_philo *next, int i);
void	lstadd_back_philo(t_philo **lst, t_philo *new);
int		atoi_philo(const char *nb);
void	ft_print(t_philo *philo, char *str);
long	ft_time(void);
void	ft_usleep(int time, int seconde);
void	ft_print(t_philo *philo, char *str);
long	ft_time(void);


#endif