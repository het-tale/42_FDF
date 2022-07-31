/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 22:24:26 by het-tale          #+#    #+#             */
/*   Updated: 2022/07/31 03:08:01 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;
	if (x < 0 || y < 0)
		return ;
	dst = data->addr + (y * data->ll + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
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
		my_mlx_pixel_put(mlx, x, y, 0xFF0000);
		x += xinc;
		y += yinc;
		i++;
	}
}

t_point	init_point(int x, int y, t_color map)
{
	t_point	p;

	p.x = (x * 20) + 300;
	p.y = (y * 20) + 100;
	p.z = map.data * 20;
	p.color = map.color;
	return (p);
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
				p1 = init_point(i, j, map[j][i]);
				p2 = init_point(i + 1, j, map[j][i + 1]);
				ddaline(p1, p2, mlx);
			}
			if (j != lines - 1)
			{
				p1 = init_point(i, j, map[j][i]);
				p3 = init_point(i, j + 1, map[j + 1][i]);
				ddaline(p1, p3, mlx);
			}
			i++;
		}
		j++;
	}
}