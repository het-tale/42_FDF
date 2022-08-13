/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 12:37:23 by het-tale          #+#    #+#             */
/*   Updated: 2022/08/13 15:23:24 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

char	**good_string(char *line)
{
	char	**split;

	split = ft_split(ft_strremove(line), ' ');
	return (split);
}

int	count_len(char *line)
{
	int		j;
	char	**split;

	j = 0;
	split = good_string(line);
	while (split[j])
		j++;
	return (j);
}

int	count_columns(char **split_list)
{
	int	columns;

	columns = 0;
	while (split_list[columns])
		columns++;
	return (columns);
}

int	columns_equality(t_list *line, t_split_list *split_list)
{
	int		columns;
	int		lines;
	int		*arr;
	int		i;
	t_split	*temp;

	i = 0;
	lines = count_lines(line);
	arr = malloc(lines * sizeof(int));
	temp = split_list->head;
	while (temp)
	{
		columns = count_columns(temp->data);
		arr[i] = columns;
		temp = temp->next;
		i++;
	}
	i = 0;
	while (i < lines - 1)
	{
		if (arr[i] != arr[i + 1])
			return (-1);
		i++;
	}
	return (columns);
}

t_color	**ft_parse_map(t_map *coord)
{
	t_parse	*prs;

	prs = init_pars(coord);
	parse_utils(prs);
	return (prs->map);
}
