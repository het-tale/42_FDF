/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 22:24:26 by het-tale          #+#    #+#             */
/*   Updated: 2022/08/02 15:01:46 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;
	if (x >= 0 && x < 1000 && y >= 0 && y < 800)
	{
		dst = data->addr + (y * data->ll + x * (data->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

// void	isometric(int *x, int *y, int z)
// {
// 	int	original_x;

// 	original_x = *x;
// 	*x = *x - *y;
// 	*y = ((original_x + *y) / 2) - z;
// }

static void iso(int *x, int *y, int z)
{
    int previous_x;
    int previous_y;

    previous_x = *x;
    previous_y = *y;
    *x = (previous_x - previous_y) * cos(0.523599);
    *y = -z + (previous_x + previous_y) * sin(0.523599);
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

	iso(&p1.x, &p1.y, p1.z);
	iso(&p2.x, &p2.y, p2.z);
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
		my_mlx_pixel_put(mlx, x, y, p1.color);
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
	p.z = map.data * 12;
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