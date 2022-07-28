/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 08:23:07 by het-tale          #+#    #+#             */
/*   Updated: 2022/04/17 15:49:15 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	count_words(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static	int	word_length(char const *s, char c)
{
	int	l;

	l = 0;
	while (s[l] && s[l] != c)
		l++;
	return (l);
}

static	char	**ft_free(int j, char **str)
{
	while (j >= 0)
	{
		free(str[j]);
		j--;
	}
	free(str);
	return (NULL);
}

static char	**fill_array(char **str, char const *s, char c)
{
	int	i;
	int	j;
	int	word_l;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			word_l = word_length(&s[i], c);
			str[j] = ft_substr(s, i, word_l);
			if (!str[j])
				return (ft_free(j, str));
			j++;
		}
		while (s[i] && s[i] != c)
			i++;
	}
	str[j] = 0;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		count;

	if (!s)
		return (0);
	count = count_words(s, c);
	str = (char **)malloc((count + 1) * sizeof(char *));
	if (!str)
		return (0);
	str = fill_array(str, s, c);
	return (str);
}
