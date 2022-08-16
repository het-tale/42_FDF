/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 20:09:34 by het-tale          #+#    #+#             */
/*   Updated: 2022/08/16 16:59:55 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "../parsing/gnl/get_next_line.h"
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
# define Z_IN 34
# define Z_OUT 31

typedef struct s_node	t_node;

struct s_node
{
	char	*data;
	t_node	*next;
};

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

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_point;

typedef struct s_zoom
{
	int	s;
	int	m;
	int	l;	
}	t_zoom;

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
	int			tx;
	int			ty;
	t_map		*coord;
	int			iso;
	t_zoom		*size;
}t_mlx;

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

typedef struct s_draw
{
	t_color	**map;
	int		lines;
	int		columns;
	t_point	p1;
	t_point	p2;
	t_point	p3;
	t_parse	*prs;
}	t_draw;

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
t_parse			*ft_parse_map(t_map *coord);
int				count_len(char *line);
int				columns_equality(t_list *line, t_split_list *split_list);
void			get_window_coordinates(int *width, int *height, t_map *map);
t_map			*init_coordinates(char *argv[]);
t_mlx			*init_canvas(char *argv[]);
void			ddaline(t_point p1, t_point p2, t_mlx *mlx);
void			draw(t_mlx *mlx);
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
void			my_mlx_pixel_put(t_mlx *data, int x, int y, int color);
void			isometric(int *x, int *y, int z);
void			ddaline(t_point p1, t_point p2, t_mlx *mlx);
void			projection(t_point *p1, t_point *p2);
#endif
