/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 12:26:26 by het-tale          #+#    #+#             */
/*   Updated: 2022/08/13 15:23:24 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_node	*new_node(char *data)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	node->data = data;
	node->next = NULL;
	return (node);
}

t_list	*new_list(void)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	list->head = NULL;
	return (list);
}

void	push_at_last(t_list *file, t_node *n)
{
	t_node	*temp;

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

t_list	*get_lines(char *argv[])
{
	int		fd;
	char	*line;
	t_list	*list;
	t_node	*n;

	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	list = new_list();
	while (line)
	{
		n = new_node(line);
		push_at_last(list, n);
		line = get_next_line(fd);
	}
	close(fd);
	return (list);
}

int	count_lines(t_list *line)
{
	int		lines;
	t_node	*temp;

	lines = 0;
	temp = line->head;
	while (temp)
	{
		lines++;
		temp = temp->next;
	}
	return (lines);
}
