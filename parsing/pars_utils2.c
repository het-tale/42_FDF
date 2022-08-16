/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 16:54:21 by het-tale          #+#    #+#             */
/*   Updated: 2022/08/16 16:55:43 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_parse	*ft_parse_map(t_map *coord)
{
	t_parse	*prs;

	prs = init_pars(coord);
	parse_utils(prs);
	return (prs);
}
