/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setParForSpr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 19:32:57 by rvena             #+#    #+#             */
/*   Updated: 2021/04/22 14:13:53 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	setParForSpr2(t_tex_data *spr,
		t_settings *t_settings, double transformY)
{
	spr->sprW = abs((int)(t_settings->sW / (transformY)));
	spr->drawStartX = -1 * spr->sprW / 2 + spr->sprScrX;
	if (spr->drawStartX < 0)
		spr->drawStartX = 0;
	spr->drawEndX = spr->sprW / 2 + spr->sprScrX;
	if (spr->drawEndX >= t_settings->sW)
		spr->drawEndX = t_settings->sW - 1;
}

double	setParForSpr(t_all_data *ever, t_sprite_data *listOfSprites,
		int i, t_tex_data *spr)
{
	double		invDet;
	double		transformX;
	double		transformY;
	t_plr_data	*pl;
	t_settings	*t_settings;

	t_settings = ever->t_settings;
	pl = ever->player;
	spr->spriteX = listOfSprites[ever->spriteOrder[i]].x - pl->posX;
	spr->spriteY = listOfSprites[ever->spriteOrder[i]].y - pl->posY;
	invDet = 1 / (pl->planeX * pl->dirY - pl->dirX * pl->planeY);
	transformX = invDet * (pl->dirY * spr->spriteX - pl->dirX * spr->spriteY);
	transformY = invDet * (-1 * pl->planeY * spr->spriteX
			+ pl->planeX * spr->spriteY);
	spr->sprScrX = (int)((t_settings->sW / 2) * (1 + transformX / transformY));
	spr->sprH = abs((int)(t_settings->sH / transformY));
	spr->drawStartY = -1 * spr->sprH / 2 + t_settings->sH / 2;
	if (spr->drawStartY < 0)
		spr->drawStartY = 0;
	spr->drawEndY = spr->sprH / 2 + t_settings->sH / 2;
	if (spr->drawEndY >= t_settings->sH)
		spr->drawEndY = t_settings->sH - 1;
	setParForSpr2(spr, t_settings, transformY);
	return (transformY);
}
