/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawSprite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:20:27 by rvena             #+#    #+#             */
/*   Updated: 2021/04/18 19:34:35 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	drawSprite2(all_data *ever, int texX, int y, int sprite)
{
	tex_data	*spr;
	int			texY;
	char		*color;
	int			d;
	settings	*set;

	set = ever->settings;
	spr = ever->sprite1;
	while (y < spr->drawEndY)
	{
		d = y * 256 - set->sH * 128 + spr->sprH * 128;
		texY = ((d * spr->texHeight) / spr->sprH) / 256;
		color = spr->addr + (texY * spr->line_length
				+ texX * (spr->bits_per_pixel / 8));
		if (*(int *)color != 0)
			my_mlx_pixel_put(ever->img, sprite, y, *(int *)color);
		y++;
	}
}

void	drawSprite(all_data *ever, tex_data	*spr, settings *set, double trFY)
{
	int		sprite;
	int		y;
	int		texX;

	sprite = spr->drawStartX;
	while (sprite < spr->drawEndX)
	{
		texX = (int)(256 * (sprite - (-1 * spr->sprW / 2 + spr->sprScrX))
				* ever->sprite1->texWidth / spr->sprW) / 256;
		y = spr->drawStartY;
		if (trFY > 0 && sprite < set->sW
			&& trFY < ever->raycasting->Zbuffer[sprite])
			drawSprite2(ever, texX, y, sprite);
		sprite++;
	}
}

void	sortDist2(all_data *ever, sprite_data *listOfSpr, settings *set)
{
	int	i;

	i = 0;
	while (i < ever->numOfSprite)
	{
		setAndDraw(ever, listOfSpr, i, set);
		i++;
	}
}

void	sortDist(all_data *ever, sprite_data *listOfSprites, settings *settings)
{
	int		i;
	int		j;
	double	tempDist;
	int		tempOrd;

	j = ever->numOfSprite;
	i = 0;
	while (i < ever->numOfSprite)
	{
		while (j > i)
		{
			if (ever->spriteDist[j - 1] < ever->spriteDist[j])
			{
				tempDist = ever->spriteDist[j - 1];
				ever->spriteDist[j - 1] = ever->spriteDist[j];
				ever->spriteDist[j] = tempDist;
				tempOrd = ever->spriteOrder[j - 1];
				ever->spriteOrder[j - 1] = ever->spriteOrder[j];
				ever->spriteOrder[j] = tempOrd;
			}
			j--;
		}
		i++;
	}
	sortDist2(ever, listOfSprites, settings);
}

void	setAndSort(all_data *ever, sprite_data *listOfSpr, settings *set)
{
	player_data	*pl;
	int			j;

	j = 0;
	pl = ever->player;
	while (j < ever->numOfSprite)
	{
		ever->spriteOrder[j] = j;
		ever->spriteDist[j] = (pl->posX - listOfSpr[j].x)
			* (pl->posX - listOfSpr[j].x) + (pl->posY - listOfSpr[j].y)
			* (pl->posY - listOfSpr[j].y);
		j++;
	}
	sortDist(ever, listOfSpr, set);
}
