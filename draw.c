/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 22:24:26 by het-tale          #+#    #+#             */
/*   Updated: 2022/08/09 19:13:10 by het-tale         ###   ########.fr       */
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
	int		dx;
	int		dy;
	int		steps;
	int		i;
	float	xinc;
	float	yinc;
	float	x;
	float	y;

	isometric(&p1.x, &p1.y, p1.z);
	isometric(&p2.x, &p2.y, p2.z);
	dx = abs(p1.x - p2.x);
	dy = abs(p1.y - p2.y);
	if (dx > dy)
		steps = dx;
	else
		steps = dy;
	xinc = (p2.x - p1.x) / (float) steps;
	yinc = (p2.y - p1.y) / (float) steps;
	x = p1.x;
	y = p1.y;
	i = 0;
	while (i <= steps)
	{
		my_mlx_pixel_put(mlx, x + (mlx->win_width / 2), y + (mlx->win_height / 500), p1.color);
		x += xinc;
		y += yinc;
		i++;
	}
}

// int	zoom(int key, int *z)
// {
// 	if (key == 126)
// 		*z += 1;
// 	else if (key == 125)
// 		*z -= 1;
// 	// (void)key;
// 	// (void)z;
// 	// printf("hello");
// 	return (0);
// }

t_point	init_point(int x, int y, t_color mapi, t_map *map, t_mlx *mlx)
{
	t_point	p1;
	// int		zoom1;

	// zoom1 = 0;
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
	//mlx_key_hook(mlx->mlx_win, zoom, &zoom1);
	(void)mlx;
	p1.z = mapi.data * 2;
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
}