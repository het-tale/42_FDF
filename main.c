/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 05:03:32 by het-tale          #+#    #+#             */
/*   Updated: 2022/08/10 12:04:39 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	destroy_window(int key, t_mlx *param)
{
	if (key == 53)
	{
		mlx_destroy_window(param->mlx, param->mlx_win);
		exit(0);
	}
	return (0);
}

int	ft_exit(void)
{
	exit(0);
}

void	get_window_coordinates(int *win_width, int *win_height, t_map *map)
{
	if (map->columns <= 50 || map->lines <= 50)
	{
		*win_width = (map->columns) * 28;
		*win_height = (map->lines) * 16;
	}
	else if ((map->columns > 50 || map->lines > 50) && (map->columns <= 100 || map->lines <= 100))
	{
		*win_width = (map->columns) * 6;
		*win_height = (map->lines) * 6;
	}
	else
	{
		*win_width = (map->columns) * 4;
		*win_height = (map->lines) * 4;
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

t_mlx	*init_canvas(char *argv[])
{
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx));
	mlx->mlx = mlx_init();
	mlx->zoom = 0;
	mlx->coord = init_coordinates(argv);
	get_window_coordinates(&mlx->win_width, &mlx->win_height, mlx->coord);
	mlx->mlx_win = mlx_new_window(mlx->mlx, mlx->win_width, mlx->win_height, "my fdf");
	return (mlx);
}

void	errors(char *argv[], t_map *coord)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (coord->columns == -1)
	{
		write(2, "Found wrong line length. Exiting.\n", 34);
		ft_exit();
	}
	if (fd < 0)
	{
		perror("Error");
		ft_exit();
	}
	close(fd);
	if (coord->line_list->head == NULL)
	{
		write(2, "No data found.\n", 15);
		ft_exit();
	}
}

int	main(int argc, char *argv[])
{
	t_mlx	*mlx;

	if (argc == 2)
	{
		mlx = init_canvas(argv);
		errors(argv, mlx->coord);
		draw(mlx, mlx->coord);
		mlx_key_hook(mlx->mlx_win, key_management, mlx);
		mlx_hook(mlx->mlx_win, 17, 0, ft_exit, mlx);
		mlx_loop(mlx->mlx);
	}
	else
		write(2, "Usage : ./fdf <filename> [ case_size z_size ]\n", 46);
	return (0);
}
