/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 12:18:20 by het-tale          #+#    #+#             */
/*   Updated: 2022/08/16 04:44:47 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	get_window_coordinates(int *win_width, int *win_height, t_map *map)
{
	int	columns;
	int	lines;

	columns = map->columns;
	lines = map->lines;
	if (columns <= 50 || lines <= 50)
	{
		*win_width = (columns) * 28;
		*win_height = (lines) * 16;
	}
	else if ((columns > 50 || lines > 50) && (columns <= 100 || lines <= 100))
	{
		*win_width = (columns) * 6;
		*win_height = (lines) * 6;
	}
	else
	{
		*win_width = (columns) * 4;
		*win_height = (lines) * 4;
	}
}

t_map	*init_coordinates(char *argv[])
{
	t_map	*coord;

	coord = malloc(sizeof(t_map));
	coord->line_list = get_lines(argv);
	coord->split_list = get_split(coord->line_list);
	coord->lines = count_lines(coord->line_list);
	coord->columns = columns_equality(coord->line_list, coord->split_list);
	return (coord);
}

t_zoom	*init_zoom(void)
{
	t_zoom	*zooom;

	zooom = malloc(sizeof(t_zoom));
	zooom->s = 12;
	zooom->m = 4;
	zooom->l = 2;
	return (zooom);
}

t_mlx	*init_canvas(char *argv[])
{
	t_mlx	*mlx;
	int		win_width;
	int		win_height;

	mlx = malloc(sizeof(t_mlx));
	mlx->mlx = mlx_init();
	mlx->zoom = 0;
	mlx->tx = 0;
	mlx->ty = 0;
	mlx->iso = 0;
	mlx->size = init_zoom();
	mlx->coord = init_coordinates(argv);
	get_window_coordinates(&mlx->win_width, &mlx->win_height, mlx->coord);
	win_width = mlx->win_width;
	win_height = mlx->win_height;
	mlx->mlx_win = mlx_new_window(mlx->mlx, win_width, win_height, "my fdf");
	return (mlx);
}
