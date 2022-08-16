/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 03:03:41 by het-tale          #+#    #+#             */
/*   Updated: 2022/08/16 16:28:39 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	hex_utils(char hex, int asc, int *base)
{
	int	decimal;
	int	b;

	b = *base;
	decimal = (hex - asc) * b;
	*base *= 16;
	return (decimal);
}

int	hex_to_dec(char *hex)
{
	int	dec;
	int	i;
	int	base;

	dec = 0;
	base = 1;
	i = ft_strlen(hex) - 1;
	while (i >= 0)
	{
		if (hex[i] >= '0' && hex[i] <= '9')
			dec += hex_utils(hex[i], 48, &base);
		else if (hex[i] >= 'A' && hex[i] <= 'F')
			dec += hex_utils(hex[i], 55, &base);
		else if (hex[i] >= 'a' && hex[i] <= 'f')
			dec += hex_utils(hex[i], 87, &base);
		i--;
	}
	return (dec);
}

int	ft_strchrr(char *s1, char c)
{
	int	i;

	i = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

t_parse	*init_pars(t_map *coord)
{
	t_parse	*prs;

	prs = malloc(sizeof(t_parse));
	prs->i = 0;
	prs->split_list = coord->split_list;
	prs->temp = prs->split_list->head;
	prs->lines = coord->lines;
	prs->columns = coord->columns;
	prs->map = malloc(prs->lines * sizeof(t_color *));
	return (prs);
}

void	parse_utils(t_parse *prs)
{
	char	*substr;
	int		in;

	while (prs->temp)
	{
		prs->map[prs->i] = malloc(prs->columns * sizeof(t_color));
		prs->split = prs->temp->data;
		prs->j = 0;
		while (prs->split[prs->j])
		{
			prs->val.data = ft_atoi(prs->split[prs->j]);
			if (ft_strchrr(prs->split[prs->j], ',') != -1)
			{
				in = ft_strchrr(prs->split[prs->j], ',');
				substr = ft_substr(prs->split[prs->j], in + 3, 6);
				prs->val.color = hex_to_dec(substr);
			}
			else
				prs->val.color = hex_to_dec("FFFFFF");
			prs->map[prs->i][prs->j] = prs->val;
			prs->j++;
		}
		prs->i++;
		prs->temp = prs->temp->next;
	}
}
