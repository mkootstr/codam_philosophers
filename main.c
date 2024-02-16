/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mkootstr <mkootstr@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/26 14:03:37 by mkootstr      #+#    #+#                 */
/*   Updated: 2024/02/16 15:38:40 by mkootstr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	fatal(char *str, t_shared *shared)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(str, 2);
	write(2, "\n", 2);
	return (1);
	//hier moet nog free
}

int	check_input(t_shared *input)
{
	if (input->nr_philo < 1 || input->t_die < 1)
		return (fatal("Invalid input", input));
	if (input->t_eat < 1 || input->t_sleep < 1)
		return (fatal("Invalid input", input));
	if (input->nr_eat < 1 && input->nr_eat != -2)
		return (fatal("Invalid input", input));
	return (0);
}

t_shared	*parse(char **argv)
{
	t_shared *input;

	input = malloc(1 * sizeof(t_shared));
	if (!input)
		return (NULL);
	else
	{
		input->nr_philo = ft_atoi(argv[1]);
		input->t_die = ft_atoi(argv[2]);
		input->t_eat = ft_atoi(argv[3]);
		input->t_sleep = ft_atoi(argv[4]);
		if (argv[5] != NULL)
			input->nr_eat = ft_atoi(argv[5]);
		else 
			input->nr_eat = -2;
		if (check_input(input) == 1)
			return (NULL);
	}
	return (input);
}

int philo(char **argv)
{
	t_shared *input;

	input = NULL;
	if (argv)
	{
		input = parse(argv);
		if (input != NULL)
			return(spaghetti_time(input));
		else
			return (fatal("Input error", input));
	}
	else
		return (fatal("Input error", input));
}

t_shared *init_struct(t_shared *shared)
{
	int i;

	i = 0;
	shared->philos = malloc(shared->nr_philo * sizeof(t_philo));
	if (!shared->philos)
		return (NULL);
	while (i < shared->nr_philo)
	{
		shared->philos[i].nr = i + 1;
		shared->philos[i].eat_count = 0;
		shared->philos[i].is_eating = 0;
		shared->philos[i].last_eat = 0;
		shared->philos[i].shared = shared;
		shared->philos[i].l_fork = i;
		shared->philos[i].r_fork = i + 1;
		if (i == shared->nr_philo - 1)
			shared->philos[i].r_fork = 0;
		i++;
	}
	return (shared);
}

t_shared *init_mutexes(t_shared *shared)
{
	int i;

	i = 0;
	shared->forks = ft_malloc(shared->nr_philo * sizeof(pthread_mutex_t));
	while (i < shared->nr_philo)
	{
		if (pthread_mutex_init(&shared->forks[i], NULL) != 0)
			return (NULL);
		i++;
	}
	if (pthread_mutex_init(&shared->print, NULL) != 0)
		return (NULL);
	if (pthread_mutex_init(&shared->monitor, NULL) != 0)
		return (NULL);
}

long int get_time(t_shared *shared)
{
	t_timeval time;

	if (shared->start == 0)
	{
		gettimeofday(&time, NULL);
		shared->start = time.tv_sec * 1000 + time.tv_usec / 1000;
		return (shared->start);
	}
	else
	{
		gettimeofday(&time, NULL);
		return (time.tv_sec * 1000 + time.tv_usec / 1000 - shared->start);
	}
}

void	take_forks(t_philo *philo)
{

}

void	routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (philo->shared->dead == 0 && )
	{
		take_forks(philo);
		eat(philo);
		sleep(philo);
	}
}

void	printmessage(t_philo *philo, char *str)
{
	long long time;

	time = get_time(philo->shared->start);
	pthread_mutex_lock(&philo->shared->print);
	ft_putnbr_fd(time, 1);
	write(1, " ", 1);
	ft_putnbr_fd(philo->nr, 1);
	ft_putstr_fd(str, 1);
	pthread_mutex_unlock(&philo->shared->print);
	return ;
}

t_shared *start_threads(t_shared *shared)
{
	int i;

	i = 0;
	while (i < shared->nr_philo)
	{
		if (pthread_create(&shared->philos[i].thread, NULL, &routine, &shared->philos[i]) != 0)
		{
			while (i > 0)
			{		
				i--;
				if (pthread_join(shared->philos[i].thread, NULL) != 0)
					return (NULL);
			}
		}
		i++;
	}
	i = 0;
	while (i < shared->nr_philo)
	{
		if (pthread_join(shared->philos[i].thread, NULL) != 0)
			return (NULL);
		i++;
	}
	return (shared);
}

int spaghetti_time(t_shared *shared)
{
	if (init_struct(shared) == NULL)
		return (fatal("Malloc error", shared));
	if (init_mutexes(shared) == NULL)
		return (fatal("Mutex error", shared));
	if (start_threads(shared) == NULL)
		return (fatal ("Thread error", shared));
	free_all(shared);
	return (0);
}


int main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (fatal("Invalid input", NULL));
	else
		return (philo(argv));
}