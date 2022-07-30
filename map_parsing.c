/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 03:03:41 by het-tale          #+#    #+#             */
/*   Updated: 2022/07/30 14:51:42 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

char	**good_string(char *line)
{
	char	**split;

	split = ft_split(ft_strremove(line), ' ');
	return (split);
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

void	traverse_list(t_list *list)
{
	t_node	*temp;

	temp = list->head;
	while (temp)
	{
		printf("%s", temp->data);
		temp = temp->next;
	}
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
		j++;
	}
	split_list[j] = 0;
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
		{
			dec += (hex[i] - 48) * base;
			base *= 16;
		}
		else if (hex[i] >= 'A' && hex[i] <= 'F')
		{
			dec += (hex[i] - 55) * base;
			base *= 16;
		}
		else if (hex[i] >= 'a' && hex[i] <= 'f')
		{
			dec += (hex[i] - 87) * base;
			base *= 16;
		}
		i--;
	}
	return (dec);
}

int	ft_strchrr(char *s1, char c)
{
	int	i;
	int	d;

	i = 0;
	d = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

t_color	**ft_parse_map(char *argv[])
{
	t_split_list *split_list;
	int		j;
	t_color **map;
	t_color	val;
	int		i;
	int		lines;
	int		columns;
	t_list	*line;
	t_split		*temp;
	char		**split;

	i = 0;
	line = get_lines(argv);
	split_list = get_split(line);
	temp = split_list->head;
	lines = count_lines(line);
	columns = columns_equality(line, split_list);
	map = malloc(lines * sizeof(t_color *));
	while (temp)
	{
		map[i] = malloc(columns * sizeof(t_color));
		split = temp->data;
		j = 0;
		while (split[j])
		{
			val.data = ft_atoi(split[j]);
			if (ft_strchr(split[j], ',') != -1)
				val.color = hex_to_dec(ft_substr(split[j], ft_strchr(split[j], ',') + 3, 6));
			else
				val.color = 0;
			map[i][j] = val;
			j++;
		}
		i++;
		temp = temp->next;
	}
	return (map);
}