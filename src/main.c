/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 05:03:32 by het-tale          #+#    #+#             */
/*   Updated: 2022/08/16 04:58:25 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

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
		draw(mlx);
		mlx_key_hook(mlx->mlx_win, key_management, mlx);
		mlx_hook(mlx->mlx_win, 17, 0, ft_exit, mlx);
		mlx_loop(mlx->mlx);
		free(mlx);
	}
	else
		write(2, "Usage : ./fdf <filename> [ case_size z_size ]\n", 46);
	return (0);
}
