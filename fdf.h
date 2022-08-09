/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 20:09:34 by het-tale          #+#    #+#             */
/*   Updated: 2022/08/09 21:54:20 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "gnl/get_next_line.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <mlx.h>
# include <math.h>
# include <sys/time.h>
# include <signal.h>
# include <string.h>
# include <errno.h>
# define ESC 53
# define PLUS_KEY 69
# define MINUS_KEY 78
# define RIGHT_KEY 124
# define LEFT_KEY 123
# define UP_KEY 126
# define DOWN_KEY 125
# define PROJECT 35 //P KEY
# define ROTATION 15 // R KEY

typedef struct s_mlx
{
	void		*mlx;
	void		*mlx_win;
	void		*img;
	char		*addr;
	int			bpp;
	int			ll;
	int			end;
	char		**av;
	int			win_width;
	int			win_height;
	int			zoom;
}t_mlx;

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_point;

typedef struct s_draw
{
	int		j;
	int		i;
	int		lines;
	int		columns;
	int		**map;
	t_point	p1;
	t_point	p2;
	t_point	p3;
	int		z1;
	int		z2;
	int		z3;
}	t_draw;

typedef struct s_parse
{
	char	*line;
	char	**split;
	int		fd;	
	int		**map;
	int		*arr;
	size_t	len;
	size_t	j;
	int		i;
	int		k;
}	t_parse;

typedef struct s_color
{
	int	data;
	int	color;
}	t_color;

typedef struct s_node
{
	char			*data;
	struct s_node	*next;
}	t_node;

typedef struct s_list
{
	t_node	*head;
}	t_list;

typedef struct s_split
{
	char			**data;
	struct s_split	*next;
}	t_split;

typedef struct s__split_list
{
	t_split	*head;
}	t_split_list;

typedef struct s_map
{
	int				lines;
	int				columns;
	t_list			*line_list;
	t_split_list	*split_list;
}	t_map;

int				count_lines(t_list *line);
t_color			**ft_parse_map(t_map *coord);
int				count_len(char *line);
int				columns_equality(t_list *line, t_split_list *split_list);
void			ddaline(t_point p1, t_point p2, t_mlx *mlx);
void			draw(t_mlx *mlx, t_map *coord);
int				hex_to_dec(char *hex);
void			traverse_list(t_list *list);
t_list			*get_lines(char *argv[]);
char			**get_split_line(char *line);
t_split_list	*get_split(t_list *lines);
int				count_columns(char **split_list);
int				hex_to_dec(char *hex);
int				zoom(int key, int *z);
int				get_z(t_mlx *mlx);
int				key_management(int key, t_mlx *mlx);
//to do:change buffer size in gnl --- Done
//to do: check if the columns are equal for each line -- Done
//to do; try manage colors --- Done
//to do: error management (page correction) //DONE
//empty file: no data found //DONE
//file not found //Done
//create function to manage these errors first //DONE
//bonus IDEA: make the map appear bigger or smaller
//upper key : 126 -- lower key : 125 ----- right key : 124 ------ left key : 123
#endif
