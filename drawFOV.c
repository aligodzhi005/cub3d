/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawFOV.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 14:12:52 by rvena             #+#    #+#             */
/*   Updated: 2021/04/21 21:33:28 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	drawVertLine2(t_tex_data *temp, t_all_data *ever, int lineH, int x)
{
	double	step;
	double	texPos;
	char	*color;
	int		y;
	int		texY;

	y = 0;
	temp->texX = setTexX(ever, temp);
	step = 1.0 * temp->texHeight / lineH;
	texPos = (temp->drawStart - ever->t_settings->sH / 2 + lineH / 2)
		* step;
	while (y < ever->t_settings->sH)
	{
		if (y > temp->drawStart && y <= temp->drawEnd)
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

static t_tex_data	*chooseTex(t_all_data *everything)
{
	t_tex_data	*temp;

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

static void	drawVertLine(t_all_data *everything, int x, t_settings *t_settings)
{
	int			lineHeight;
	t_tex_data	*temp;

	temp = chooseTex(everything);
	lineHeight = (int)(t_settings->sH / everything->raycasting->perpWallDist);
	temp->drawStart = -1 * lineHeight / 2 + t_settings->sH / 2;
	if (temp->drawStart < 0)
		temp->drawStart = 0;
	temp->drawEnd = lineHeight / 2 + t_settings->sH / 2;
	if (temp->drawEnd >= t_settings->sH)
		temp->drawEnd = t_settings->sH - 1;
	everything->texture = temp;
	drawVertLine2(temp, everything, lineHeight, x);
}

void	drawFOV(t_all_data *everything, char **map, t_settings *t_settings)
{
	int	x;

	x = 0;
	while (x < t_settings->sW)
	{
		setBasRayPar(everything->raycasting, everything, x, map);
		drawVertLine(everything, x, t_settings);
		x++;
	}
}
