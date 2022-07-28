/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 05:03:32 by het-tale          #+#    #+#             */
/*   Updated: 2022/07/28 16:51:42 by het-tale         ###   ########.fr       */
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

t_mlx	*init_canvas(void)
{
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx));
	mlx->mlx = mlx_init();
	mlx->mlx_win = mlx_new_window(mlx->mlx, 1000, 600, "FDF");
	mlx->img = mlx_new_image(mlx->mlx, 1000, 600);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->ll, &mlx->end);
	return (mlx);
}

int	main(int argc, char *argv[])
{
	//t_mlx	*mlx;
	int		columns;

	//columns = columns_equality(argv);
	columns = 0;
	if (argc == 2)
	{
		if (columns == -1)
		{
			write(2, "Found wrong line length. Exiting.\n", 34);
			ft_exit();
		}
		// mlx = init_canvas();
		// mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img, 0, 0);
		// mlx_key_hook(mlx->mlx_win, destroy_window, mlx);
		// mlx_hook(mlx->mlx_win, 17, 0, ft_exit, mlx);
		// mlx_loop(mlx->mlx);
		// t_color	**map;
		// t_color	val;
		// int	i;
		// int j;
		// i = 0;
		// map = ft_parse_map(argv);
		// //printf("%d ", map[0][0]);
		// while (i < count_lines(argv))
		// {
		// 	j = 0;
		// 	while (j < columns_equality(argv))
		// 	{
		// 		val = map[i][j];
		// 		//printf("%d ", val.data);
		// 		printf("%d ", val.color);
		// 		j++;
		// 	}
		// 	printf("\n");
		// 	i++;
		// }
		//traverse_list(get_lines(argv));
		printf("%d", columns_equality(get_lines(argv)));
		//printf("%d", count_columns(get_lines(argv)->head->next->data));
	}
	else
		write(2, "Usage : ./fdf <filename> [ case_size z_size ]\n", 46);
	return (0);
}
