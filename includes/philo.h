/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:06:31 by emoreau           #+#    #+#             */
/*   Updated: 2023/10/05 18:42:44 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				num;
	int				i;
	long			last_time_to_eat;
	pthread_t		thread;
	pthread_mutex_t	*fork;
	struct s_philo	*next;
	struct s_data	*data;	

}	t_philo;

typedef struct s_data
{
	int				number;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				win;
	long			start;
	int				death;
	int				see_dead;
	// pthread_mutex_t	print_dead;
	pthread_mutex_t	speak;
	pthread_mutex_t	print;
	pthread_mutex_t	dead;

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
void	free_lst(t_philo *philo);
void	philo_free(t_philo *philo, int i);
void	ft_free(t_philo *philo);
int		cheak_death(t_philo *philo);
int		take_fork(t_philo *philo);
int		eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	*routine(void *arg);
void	is_death(t_philo *philo);
int		cheak_death(t_philo *philo);
int		pars(char **av);
int		checknum(char **av);
int		all_num(char *str);
int		isdigit_philo(int c);
void	loop_a(t_philo *philo);
void	loop_b(t_philo *philo);
int		last_fork(t_philo *philo);
void usleep_loop(t_philo *philo, int b);

#endif