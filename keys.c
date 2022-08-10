/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 21:48:34 by het-tale          #+#    #+#             */
/*   Updated: 2022/08/10 14:13:51 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	draw(mlx, mlx->coord);
	return (0);
}
