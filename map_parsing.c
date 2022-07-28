/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 03:03:41 by het-tale          #+#    #+#             */
/*   Updated: 2022/07/28 16:47:59 by het-tale         ###   ########.fr       */
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

char	*good_string(char *line)
{
	char	*split;

	split = ft_strremove(line);
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

int	count_columns(char *line)
{
	int		columns;
	int		j;
	char	*split;

	columns = 0;
	j = 0;
	split = good_string(line);
	while (split[j])
	{
		columns++;
		j++;
	}
	return (columns);
}

int	columns_equality(t_list *line)
{
	int		columns;
	int		lines;
	int		*arr;
	int		i;
	t_node	*temp;

	i = 0;
	lines = count_lines(line);
	arr = malloc(lines * sizeof(int));
	temp = line->head;
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

// int	hex_to_dec(char *hex)
// {
// 	int	dec;
// 	int	i;
// 	int	base;

// 	dec = 0;
// 	base = 1;
// 	i = ft_strlen(hex) - 1;
// 	while (i >= 0)
// 	{
// 		if (hex[i] >= '0' && hex[i] <= '9')
// 		{
// 			dec += (hex[i] - 48) * base;
// 			base *= 16;
// 		}
// 		else if (hex[i] >= 'A' && hex[i] <= 'F')
// 		{
// 			dec += (hex[i] - 55) * base;
// 			base *= 16;
// 		}
// 		else if (hex[i] >= 'a' && hex[i] <= 'f')
// 		{
// 			dec += (hex[i] - 87) * base;
// 			base *= 16;
// 		}
// 		i--;
// 	}
// 	return (dec);
// }

// int	ft_strchrr(char *s1, char c)
// {
// 	int	i;
// 	int	d;

// 	i = 0;
// 	d = 0;
// 	while (s1[i] != '\0')
// 	{
// 		if (s1[i] == c)
// 			return (i);
// 		i++;
// 	}
// 	return (-1);
// }

// t_color	**ft_parse_map(char *argv[])
// {
// 	char	**split;
// 	int		fd;
// 	char	*line;
// 	int		j;
// 	//int		**map;
// 	t_color **map;
// 	t_color	val;
// 	int		i;
// 	int		lines;
// 	int		columns;
// 	t_list	*line;
// 	t_node	*temp;

// 	i = 0;
// 	line = get_lines(argv);
// 	temp = line->head;
// 	lines = count_lines(line);
// 	columns = columns_equality(line, split);
// 	//map = malloc(lines * sizeof(int *));
// 	map = malloc(lines * sizeof(t_color *));
// 	while (line)
// 	{
// 		split = good_string(line);
// 		//map[i] = malloc(columns * sizeof(int));
// 		map[i] = malloc(columns * sizeof(t_color));
// 		j = 0;
// 		while (split[j])
// 		{
// 			val.data = ft_atoi(split[j]);
// 			if (ft_strchr(split[j], ',') != -1)
// 				val.color = hex_to_dec(ft_substr(split[j], ft_strchr(split[j], ',') + 3, 6));
// 			else
// 				val.color = 0;
// 			//map[i][j] = ft_atoi(split[j]);
// 			map[i][j] = val;
// 			j++;
// 		}
// 		i++;
// 		line = get_next_line(fd);
// 	}
// 	return (map);
// }