/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 20:09:34 by het-tale          #+#    #+#             */
/*   Updated: 2022/08/10 14:18:50 by het-tale         ###   ########.fr       */
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
	t_map		*coord;
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

typedef struct s_color
{
	int	data;
	int	color;
}	t_color;

typedef struct s_parse
{
	t_split_list	*split_list;
	int				j;
	t_color			**map;
	t_color			val;
	int				i;
	int				lines;
	int				columns;
	t_split			*temp;
	char			**split;
}	t_parse;

typedef struct s_dda
{
	int		dx;
	int		dy;
	int		steps;
	int		i;
	float	xinc;
	float	yinc;
	float	x;
	float	y;
	float	start_x;
	float	start_y;
}	t_dda;


int				count_lines(t_list *line);
t_color			**ft_parse_map(t_map *coord);
int				count_len(char *line);
int				columns_equality(t_list *line, t_split_list *split_list);
void			get_window_coordinates(int *width, int *height, t_map *map);
t_map			*init_coordinates(char *argv[]);
t_mlx			*init_canvas(char *argv[]);
void			ddaline(t_point p1, t_point p2, t_mlx *mlx);
void			draw(t_mlx *mlx, t_map *coord);
//parsing
t_node			*new_node(char *data);
t_list			*new_list(void);
void			push_at_last(t_list *file, t_node *n);
t_list			*get_lines(char *argv[]);
int				hex_to_dec(char *hex);
t_split			*new_node_split(char **data);
t_split_list	*new_list_split(void);
void			push_at_last_split(t_split_list *file, t_split *n);
char			**get_split_line(char *line);
t_split_list	*get_split(t_list *lines);
char			**good_string(char *line);
int				count_columns(char **split_list);
int				hex_to_dec(char *hex);
int				ft_strchrr(char *s1, char c);
int				zoom(int key, int *z);
int				get_z(t_mlx *mlx);
int				key_management(int key, t_mlx *mlx);
void			parse_utils(t_parse *prs);
t_parse			*init_pars(t_map *coord);
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
