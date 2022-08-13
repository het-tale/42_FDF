/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:29:00 by het-tale          #+#    #+#             */
/*   Updated: 2022/07/28 16:55:57 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strremove(const char *s1)
{
	char	*s2;
	size_t	len;
	int		i;
	int		j;

	len = ft_strlen(s1);
	s2 = (char *)malloc((len + 1) * sizeof(char));
	if (!s2)
		return (0);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		while (s1[i] == '\n')
			i++;
		if (s1[i] == '\0')
		{
			s2[j] = '\0';
			break ;
		}
		s2[j] = s1[i];
		i++;
		j++;
	}
	return (s2);
}
