/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 12:45:44 by het-tale          #+#    #+#             */
/*   Updated: 2021/12/12 01:57:54 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	if (!str)
		return (0);
	while (str[count] != '\0')
		count++;
	return (count);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*rest;
	size_t	count;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	count = ft_strlen(s1) + ft_strlen(s2) + 1;
	rest = (char *) malloc (sizeof(char) * count);
	if (!rest)
		return (NULL);
	while (s1[i] != '\0')
		rest[j++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		rest[j++] = s2[i++];
	rest[j] = '\0';
	free(s1);
	return (rest);
}

int	ft_strchr(char *s, int c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == (char )c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_read(int *rb, char *temp, char *buf, int fd)
{
	int	k;

	k = *rb;
	while (k > 0 && !ft_strchr(buf, '\n'))
	{
		k = read(fd, temp, BUFFER_SIZE);
		if (k < 0)
		{
			free(buf);
			free(temp);
			return (NULL);
		}
		temp[k] = 0;
		buf = ft_strjoin(buf, temp);
	}
	free(temp);
	*rb = k;
	return (buf);
}

char	*get_next_line(int fd)
{
	char		*temp;
	char		*str;
	static char	*buf = NULL;
	int			k;

	k = 1;
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	temp = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	buf = ft_read(&k, temp, buf, fd);
	if (buf == NULL)
		return (NULL);
	if (k == 0 && (!buf || buf[0] == '\0'))
	{
		free(buf);
		buf = NULL;
		return (NULL);
	}
	str = extract_line(buf);
	buf = extract_after_line(buf);
	return (str);
}
