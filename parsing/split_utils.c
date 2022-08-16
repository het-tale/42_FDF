/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 12:31:10 by het-tale          #+#    #+#             */
/*   Updated: 2022/08/16 03:05:16 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_split	*new_node_split(char **data)
{
	t_split	*node;

	node = malloc(sizeof(t_split));
	node->data = data;
	node->next = NULL;
	return (node);
}

t_split_list	*new_list_split(void)
{
	t_split_list	*list;

	list = malloc(sizeof(t_split_list));
	list->head = NULL;
	return (list);
}

void	push_at_last_split(t_split_list *file, t_split *n)
{
	t_split	*temp;

	temp = file->head;
	if (file->head == NULL)
		file->head = n;
	else
	{
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = n;
		n->next = NULL;
	}
}

char	**get_split_line(char *line)
{
	char	**split;
	char	**split_list;
	int		columns;
	int		j;

	columns = count_len(line);
	split = good_string(line);
	split_list = malloc((columns + 1) * sizeof(char *));
	j = 0;
	while (split[j])
	{
		split_list[j] = malloc((ft_strlen(split[j]) + 1) * sizeof(char));
		split_list[j] = split[j];
		free(split[j]);
		j++;
	}
	split_list[j] = 0;
	free(split);
	return (split_list);
}

t_split_list	*get_split(t_list *lines)
{
	t_split_list	*split_list;
	t_node			*temp;
	t_split			*n;
	char			**split;

	temp = lines->head;
	split_list = new_list_split();
	while (temp)
	{
		split = get_split_line(temp->data);
		n = new_node_split(split);
		push_at_last_split(split_list, n);
		temp = temp->next;
	}
	return (split_list);
}
