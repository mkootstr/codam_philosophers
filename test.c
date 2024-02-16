/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mkootstr <mkootstr@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/18 18:27:32 by mkootstr      #+#    #+#                 */
/*   Updated: 2024/02/16 15:35:47 by mkootstr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

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
			printf("%ld\n", start);
		}
		else
		{
			gettimeofday(&time, NULL);
			printf("%ld\n",(time.tv_sec * 1000 + time.tv_usec / 1000 - start));
		}
		usleep(300000);
	}
	return (0);
}