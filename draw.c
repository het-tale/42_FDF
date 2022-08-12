/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 22:24:26 by het-tale          #+#    #+#             */
/*   Updated: 2022/08/12 22:56:58 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	init_point(int x, int y, t_color mapi, t_mlx *mlx)
{
	t_point	p1;

	if (mlx->coord->columns <= 50 || mlx->coord->lines <= 50)
	{
		p1.x = x * 12;
		p1.y = y * 12;
	}
	else if ((mlx->coord->columns > 50 || mlx->coord->lines > 50)
		&& (mlx->coord->columns <= 100 || mlx->coord->lines <= 100))
	{
		p1.x = x * 4;
		p1.y = y * 4;
	}
	else
	{
		p1.x = x * 2;
		p1.y = y * 2;
	}
	p1.z = mapi.data * mlx->zoom;
	p1.color = mapi.color;
	return (p1);
}

t_draw	*init_draw(t_mlx *mlx)
{
	t_draw	*draw;

	draw = malloc(sizeof(t_draw));
	draw->lines = mlx->coord->lines;
	draw->columns = mlx->coord->columns;
	draw->map = ft_parse_map(mlx->coord);
	mlx->img = mlx_new_image(mlx->mlx, mlx->win_width, mlx->win_height);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->ll, &mlx->end);
	return (draw);
}

void	draw_point(int i, int j, t_draw *draw, t_mlx *mlx)
{
	draw->p1 = init_point(i, j, draw->map[j][i], mlx);
	draw->p2 = init_point(i + 1, j, draw->map[j][i + 1], mlx);
	ddaline(draw->p1, draw->p2, mlx);
}

void	draw(t_mlx *mlx)
{
	t_draw	*draw;
	int		i;
	int		j;

	j = 0;
	draw = init_draw(mlx);
	while (j < draw->lines)
	{
		i = 0;
		while (i < draw->columns)
		{
			if (i != draw->columns - 1)
				draw_point(i, j, draw, mlx);
			if (j != draw->lines - 1)
			{
				draw->p1 = init_point(i, j, draw->map[j][i], mlx);
				draw->p3 = init_point(i, j + 1, draw->map[j + 1][i], mlx);
				ddaline(draw->p1, draw->p3, mlx);
			}
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img, 0, 0);
}
