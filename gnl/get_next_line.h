/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 12:53:22 by het-tale          #+#    #+#             */
/*   Updated: 2022/07/28 12:16:27 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 2000
# include <stdlib.h>
# include <unistd.h>

size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strchr(char *s, int c);
char	*extract_line(char *str);
char	*extract_after_line(char *str);
char	*get_next_line(int fd);
char	*ft_read(int *rb, char *temp, char *buf, int fd);
void	skip_line(char *str, int *j);
char	*ft_cpy(char *str, int *i, int *j);
char	*ft_strremove(const char *s1);
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int     ft_atoi(char *str);
#endif
