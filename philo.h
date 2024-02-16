/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mkootstr <mkootstr@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/16 15:07:27 by mkootstr      #+#    #+#                 */
/*   Updated: 2024/02/16 15:14:27 by mkootstr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stddef.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct timeval t_timeval;

typedef struct s_shared
{
	ssize_t nr_philo;
	int start;
	ssize_t t_die;
	ssize_t t_eat;
	ssize_t t_sleep;
	ssize_t nr_eat;
	ssize_t dead;
	t_philo *philos;
	pthread_mutex_t dead;
	pthread_mutex_t full;
	pthread_mutex_t *forks;
	pthread_mutex_t print;
	pthread_mutex_t monitor;
} t_shared;

typedef struct s_philo
{
	int	nr;
	int l_fork;
	int r_fork;
	int eat_count;
	int is_eating;
	long long last_eat;
	pthread_t thread;
	t_shared *shared;
} t_philo;