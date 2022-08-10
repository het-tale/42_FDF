/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 22:24:26 by het-tale          #+#    #+#             */
/*   Updated: 2022/08/10 14:21:53 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < data->win_width && y >= 0 && y < data->win_height)
	{
		dst = data->addr + (y * data->ll + x * (data->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	isometric(int *x, int *y, int z)
{
	int	original_x;

	original_x = *x;
	*x = *x - *y;
	*y = ((original_x + *y) / 2) - z;
}

void	ddaline(t_point p1, t_point p2, t_mlx *mlx)
{
	t_dda	*dda;

	isometric(&p1.x, &p1.y, p1.z);
	isometric(&p2.x, &p2.y, p2.z);
	dda = malloc(sizeof(t_dda));
	dda->dx = abs(p1.x - p2.x);
	dda->dy = abs(p1.y - p2.y);
	
	if (dda->dx > dda->dy)
		dda->steps = dda->dx;
	else
		dda->steps = dda->dy;
	dda->xinc = (p2.x - p1.x) / (float) dda->steps;
	dda->yinc = (p2.y - p1.y) / (float) dda->steps;
	dda->x = p1.x;
	dda->y = p1.y;
	dda->i = 0;
	while (dda->i <= dda->steps)
	{
		//dda->start_x = ;
		//dda->start_x = ;
		my_mlx_pixel_put(mlx, dda->x +(mlx->win_width / 2), dda->y + (mlx->win_height / 500), p1.color);
		dda->x += dda->xinc;
		dda->y += dda->yinc;
		dda->i++;
	}
}

t_point	init_point(int x, int y, t_color mapi, t_map *map, t_mlx *mlx)
{
	t_point	p1;

	if (map->columns <= 50 || map->lines <= 50)
	{
		p1.x = x * 12;
        p1.y = y * 12;
	}
	else if ((map->columns > 50 || map->lines > 50) && (map->columns <= 100 || map->lines <= 100))
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

void	draw(t_mlx *mlx, t_map *coord)
{
	t_color	**map;
	int		lines;
	int		columns;
	int		i;
	int		j;
	t_point	p1;
	t_point	p2;
	t_point	p3;

	j = 0;
	lines = coord->lines;
	columns = coord->columns;
	map = ft_parse_map(coord);
	mlx->img = mlx_new_image(mlx->mlx, mlx->win_width, mlx->win_height);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->ll, &mlx->end);
	while (j < lines)
	{
		i = 0;
		while (i < columns)
		{
			if (i != columns - 1)
			{
				p1 = init_point(i, j, map[j][i], coord, mlx);
				p2 = init_point(i + 1, j, map[j][i + 1], coord, mlx);
				ddaline(p1, p2, mlx);
			}
			if (j != lines - 1)
			{
				p1 = init_point(i, j, map[j][i], coord, mlx);
				p3 = init_point(i, j + 1, map[j + 1][i], coord, mlx);
				ddaline(p1, p3, mlx);
			}
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img, 0, 0);
}