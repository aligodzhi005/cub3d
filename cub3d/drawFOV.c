/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawFOV.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 14:12:52 by rvena             #+#    #+#             */
/*   Updated: 2021/04/18 15:47:39 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static void drawPixel()
// static int	setTexX(all_data *everything, tex_data *temp)
// {
// 	int	texX;

// 	texX = (int)(everything->raycasting->wallX * (double)temp->texWidth);
// 	if (everything->raycasting->side == 0
// 		&& everything->raycasting->rayDirX > 0)
// 		texX = temp->texWidth - texX - 1;
// 	if (everything->raycasting->side == 1
// 		&& everything->raycasting->rayDirY < 0)
// 		texX = temp->texWidth - texX - 1;
// 	return (texX);
// }

static void	drawVertLine2(tex_data *temp, all_data *ever, int lineH, int x)
{
	double	step;
	double	texPos;
	char	*color;
	int		y;
	int		texY;

	y = 0;
	temp->texX = setTexX(ever, temp);
	step = 1.0 * temp->texHeight / lineH;
	texPos = (temp->drawStart - ever->settings->sH / 2 + lineH / 2)
		* step;
	while (y < ever->settings->sH)
	{
		if (y >= temp->drawStart && y <= temp->drawEnd)
		{
			texY = (int)texPos;
			texPos += step;
			color = temp->addr +(texY * temp->line_length
					+ temp->texX * (temp->bits_per_pixel / 8));
			my_mlx_pixel_put(ever->img, x, y, *(int *)color);
		}
		drawFloorCeil(temp, ever, x, y);
		y++;
	}
}

static tex_data	*chooseTex(all_data *everything)
{
	tex_data	*temp;

	if (everything->raycasting->side == 0)
	{
		if (everything->raycasting->mapX < everything->player->posX)
			temp = &everything->tex_mas[3];
		else
			temp = &everything->tex_mas[2];
	}
	else
	{
		if (everything->raycasting->mapY < everything->player->posY)
			temp = &everything->tex_mas[1];
		else
			temp = &everything->tex_mas[0];
	}
	return (temp);
}

static void	drawVertLine(all_data *everything, int x, settings *settings)
{
	int			lineHeight;
	tex_data	*temp;

	temp = chooseTex(everything);
	lineHeight = (int)(settings->sH / everything->raycasting->perpWallDist);
	temp->drawStart = -1 * lineHeight / 2 + settings->sH / 2;
	if (temp->drawStart < 0)
		temp->drawStart = 0;
	temp->drawEnd = lineHeight / 2 + settings->sH / 2;
	if (temp->drawEnd >= settings->sH)
		temp->drawEnd = settings->sH - 1;
	everything->texture = temp;
	drawVertLine2(temp, everything, lineHeight, x);
}

void	drawFOV(all_data *everything, char **map, settings *settings)
{
	int	x;

	x = 0;
	while (x < settings->sW)
	{
		setBasRayPar(everything->raycasting, everything, x, map);
		drawVertLine(everything, x, settings);
		x++;
	}
}
