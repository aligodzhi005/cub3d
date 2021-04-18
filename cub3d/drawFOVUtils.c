/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawFOVUtils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 15:27:23 by rvena             #+#    #+#             */
/*   Updated: 2021/04/18 15:29:45 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	drawFloorCeil(tex_data *temp, all_data *everything, int x, int y)
{
	if (y < temp->drawStart)
		my_mlx_pixel_put(everything->img, x, y, everything->settings->ceilling);
	else if (y > temp->drawEnd)
		my_mlx_pixel_put(everything->img, x, y, everything->settings->floor);
}

int	setTexX(all_data *everything, tex_data *temp)
{
	int	texX;

	texX = (int)(everything->raycasting->wallX * (double)temp->texWidth);
	if (everything->raycasting->side == 0
		&& everything->raycasting->rayDirX > 0)
		texX = temp->texWidth - texX - 1;
	if (everything->raycasting->side == 1
		&& everything->raycasting->rayDirY < 0)
		texX = temp->texWidth - texX - 1;
	return (texX);
}
