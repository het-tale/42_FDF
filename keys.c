/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 21:48:34 by het-tale          #+#    #+#             */
/*   Updated: 2022/08/13 00:57:27 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	projection(t_point *p1, t_point *p2)
{
	isometric(&p1->x, &p1->y, p1->z);
	isometric(&p2->x, &p2->y, p2->z);
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
	else if (key == PROJECT)
		mlx->iso = 1;
	mlx_clear_window(mlx->mlx, mlx->mlx_win);
	draw(mlx);
	return (0);
}
