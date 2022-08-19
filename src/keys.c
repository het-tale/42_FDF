/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 21:48:34 by het-tale          #+#    #+#             */
/*   Updated: 2022/08/19 20:25:47 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	projection(t_point *p1, t_point *p2)
{
	isometric(&p1->x, &p1->y, p1->z);
	isometric(&p2->x, &p2->y, p2->z);
}

void	zoom_out(t_zoom *size)
{
	if (size->s == 0 || size->l == 0 || size->m == 0)
	{
		size->s = 1;
		size->l = 1;
		size->m = 1;
	}
	size->s *= 2;
	size->l *= 2;
	size->m *= 2;
}

void	zoom_in(t_zoom *size)
{
	size->s /= 2;
	size->l /= 2;
	size->m /= 2;
}

void	key_management_utils(int key, t_mlx *mlx)
{
	if (key == PROJECT)
	{
		if (mlx->iso == 0)
			mlx->iso = 1;
		else
			mlx->iso = 0;
	}
	else if (key == Z_OUT)
		zoom_in(mlx->size);
	else if (key == Z_IN)
		zoom_out(mlx->size);
}

int	key_management(int key, t_mlx *mlx)
{
	if (key == PLUS_KEY)
		mlx->zoom += 1;
	else if (key == MINUS_KEY)
		mlx->zoom -= 1;
	else if (key == ESC)
	{
		mlx_destroy_window(mlx->mlx, mlx->mlx_win);
		exit(0);
	}
	else if (key == RIGHT_KEY)
		mlx->tx += 10;
	else if (key == LEFT_KEY)
		mlx->tx -= 10;
	else if (key == UP_KEY)
		mlx->ty -= 10;
	else if (key == DOWN_KEY)
		mlx->ty += 10;
	else
		key_management_utils(key, mlx);
	mlx_clear_window(mlx->mlx, mlx->mlx_win);
	draw(mlx);
	return (0);
}
