/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setParForSpr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 19:32:57 by rvena             #+#    #+#             */
/*   Updated: 2021/04/18 19:36:26 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	setParForSpr2(tex_data *spr, settings *settings, double transformY)
{
	spr->sprW = abs((int)(settings->sW / (transformY)));
	spr->drawStartX = -1 * spr->sprW / 2 + spr->sprScrX;
	if (spr->drawStartX < 0)
		spr->drawStartX = 0;
	spr->drawEndX = spr->sprW / 2 + spr->sprScrX;
	if (spr->drawEndX >= settings->sW)
		spr->drawEndX = settings->sW - 1;
}

double	setParForSpr(all_data *ever, sprite_data *listOfSprites,
		int i, tex_data *spr)
{
	double		invDet;
	double		transformX;
	double		transformY;
	player_data	*pl;
	settings	*settings;

	settings = ever->settings;
	pl = ever->player;
	spr->spriteX = listOfSprites[ever->spriteOrder[i]].x - pl->posX;
	spr->spriteY = listOfSprites[ever->spriteOrder[i]].y - pl->posY;
	invDet = 1 / (pl->planeX * pl->dirY - pl->dirX * pl->planeY);
	transformX = invDet * (pl->dirY * spr->spriteX - pl->dirX * spr->spriteY);
	transformY = invDet * (-1 * pl->planeY * spr->spriteX
			+ pl->planeX * spr->spriteY);
	spr->sprScrX = (int)((settings->sW / 2) * (1 + transformX / transformY));
	spr->sprH = abs((int)(settings->sH / transformY));
	spr->drawStartY = -1 * spr->sprH / 2 + settings->sH / 2;
	if (spr->drawStartY < 0)
		spr->drawStartY = 0;
	spr->drawEndY = spr->sprH / 2 + settings->sH / 2;
	if (spr->drawEndY >= settings->sH)
		spr->drawEndY = settings->sH - 1;
	setParForSpr2(spr, settings, transformY);
	return (transformY);
}
