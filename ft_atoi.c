/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mkootstr <mkootstr@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/26 14:41:11 by mkootstr      #+#    #+#                 */
/*   Updated: 2024/03/04 16:54:22 by mkootstr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_isdigit(int a)
{
	if (a >= '0' && a <= '9')
		return (1);
	else
		return (0);
}

static int	ft_num(char *str, int i)
{
	int j;
	int num;

	j = 0;
	while (str[i] >= 48 && str[i] <= 57)
	{
		if (j == 0)
			num = str[i] - 48;
		else if (j <= 10 && num <= 214748364 && str[i] <= '9' && str[i] >= '0')
			num = num * 10 + (str[i] - 48);
		i++;
		j++;
	}
	if (j != 0 && str[i] == '\0')
		return (num);
	else
		return (-1);
}

static int	ft_minus(char c)
{
	if (ft_isdigit(c) == 1)
		return (1);
	else
		return (-1);
}

int			ft_atoi(char *str)
{
	int i;
	int num;

	i = 0;
	if (str == NULL)
		return (-1);
	if (ft_minus(str[i]) == -1)
		return (-1);
	if (str[i] == '0' && str[i + 1] != '\0')
		return (-1);
	else if (str[i] == '\0')
		return (-1);
	return (ft_num(str, i));
}
