/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mkootstr <mkootstr@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/18 18:27:32 by mkootstr      #+#    #+#                 */
/*   Updated: 2024/03/04 17:10:54 by mkootstr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void ft_putnbr_base(unsigned long num, unsigned long base, int cap)
{
	if (num / base > 0)
		ft_putnbr_base((num / base), base, cap);
    if (num % base < 10 && num >= 0)
		ft_putchar_fd((num % base + 48), 1);
    else if (num % base > 9)
        ft_putchar_fd((num % base % 10 + cap), 1);
}


int main(void)
{
	long int start;

	start = 0;
	struct timeval time;
	while (1)
	{
		if (start == 0)
		{
			gettimeofday(&time, NULL);
			start = time.tv_sec * 1000 + time.tv_usec / 1000;
			ft_putnbr_base(0, 10, 48);
			write(1, "\n", 1);
		}
		else
		{
			gettimeofday(&time, NULL);
			ft_putnbr_base((time.tv_sec * 1000 + time.tv_usec / 1000 - start), 10, 48);
			write(1, "\n", 1);
		}
		usleep(300000);
	}
	return (0);
}
