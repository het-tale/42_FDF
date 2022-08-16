/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 22:56:10 by het-tale          #+#    #+#             */
/*   Updated: 2022/08/16 04:50:52 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

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

	if (mlx->iso != 1)
		projection(&p1, &p2);
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
		dda->start_x = dda->x + (mlx->win_width / 2);
		dda->start_y = dda->y + (mlx->win_height / 500);
		my_mlx_pixel_put(mlx, dda->start_x, dda->start_y, p1.color);
		dda->x += dda->xinc;
		dda->y += dda->yinc;
		dda->i++;
	}
	free(dda);
}
