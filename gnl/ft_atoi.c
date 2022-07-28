/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 08:50:08 by het-tale          #+#    #+#             */
/*   Updated: 2022/07/26 23:08:50 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	is_space(char c)
{
	if (c == '\f' || c == '\t' || c == '\r' || \
		   	c == '\v' || c == '\n' || c == ' ')
		return (1);
	return (0);
}

int	plus(char c)
{
	if (c == '+')
		return (1);
	return (0);
}

int	minus(char c)
{
	if (c == '-')
		return (1);
	return (0);
}

int	is_numeric(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	int	i;
	int	count;
	int	res;

	i = 0;
	count = 0;
	res = 0;
	while (is_space(str[i]) == 1)
		i++;
	while (plus(str[i]) == 1 || minus(str[i]) == 1)
	{
		if (minus(str[i]) == 1)
			count++;
		i++;
	}
	while (is_numeric(str[i]) == 1)
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if (count % 2 != 0)
		res *= -1;
	return (res);
}
