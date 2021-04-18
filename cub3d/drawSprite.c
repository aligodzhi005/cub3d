/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawSprite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:20:27 by rvena             #+#    #+#             */
/*   Updated: 2021/04/18 14:58:52 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		drawSprite(all_data *ever, tex_data	*spr, settings *settings, double transformY)
{
	int		sprite;
	int		y;
	char	*color;
	int		d;
	int		texX;
	int		texY;

	sprite = spr->drawStartX;
	while (sprite < spr->drawEndX)
	{
		//printf("sprite = %d\n", sprite);
		texX = (int)(256 * (sprite - (-1 * spr->sprW / 2 + spr->spriteScreenX)) * ever->sprite1->texWidth / spr->sprW) / 256;
		y = spr->drawStartY;
		if(transformY > 0 && sprite < settings->sW && transformY < ever->raycasting->Zbuffer[sprite])
		while (y < spr->drawEndY)
		{
			//printf("y = %d\n", y);
			d = y * 256 - settings->sH * 128 + spr->spriteHeight * 128;
			texY = ((d * spr->texHeight) / spr->spriteHeight) / 256;
			color = spr->addr + (texY * spr->line_length + texX * (spr->bits_per_pixel / 8));
			//printf("color = %d\n", *(int *)color);
			if(*(int *)color != 0)
				my_mlx_pixel_put(ever->img, sprite, y, *(int *)color);
			y++;
		}
		sprite++;
	}
}

static void setParForSpr2(tex_data *spr, settings *settings, double transformY)
{
	spr->sprW = abs((int)(settings->sW / (transformY)));
	spr->drawStartX = -1 * spr->sprW / 2 + spr->spriteScreenX;
	if (spr->drawStartX < 0)
		spr->drawStartX = 0;
	spr->drawEndX = spr->sprW / 2 + spr->spriteScreenX;
	if (spr->drawEndX >= settings->sW)
		spr->drawEndX = settings->sW - 1;
}

static double setParForSpr(all_data *ever, sprite_data *listOfSprites, int i)
{
	double		invDet;//локальная переменная
	double		transformX;
	double		transformY;
	player_data *pl;//оставляю
	tex_data	*spr;
	settings	*settings;

	settings = ever->settings;
	pl = ever->player;
	spr = ever->sprite1;
	
	spr->spriteX = listOfSprites[ever->spriteOrder[i]].x - pl->posX;
	spr->spriteY = listOfSprites[ever->spriteOrder[i]].y - pl->posY;
	invDet = 1 / (pl->planeX * pl->dirY - pl->dirX * pl->planeY);
	
	transformX = invDet * (pl->dirY * spr->spriteX - pl->dirX * spr->spriteY);
	transformY = invDet * (-1 * pl->planeY * spr->spriteX + pl->planeX * spr->spriteY);
	
	spr->spriteScreenX = (int)((settings->sW / 2) * (1 + transformX / transformY));
	spr->spriteHeight = abs((int)(settings->sH / transformY));
	spr->drawStartY = -1 * spr->spriteHeight / 2 + settings->sH / 2;
	if(spr->drawStartY < 0)
		spr->drawStartY = 0;
	spr->drawEndY = spr->spriteHeight / 2 + settings->sH / 2;
	if (spr->drawEndY >= settings->sH)
		spr->drawEndY = settings->sH - 1;

	setParForSpr2(spr, settings, transformY);	
	// spr->sprW = abs((int)(settings->sW / (transformY)));
	// spr->drawStartX = -1 * spr->sprW / 2 + spr->spriteScreenX;
	// if (spr->drawStartX < 0)
	// 	spr->drawStartX = 0;
	// spr->drawEndX = spr->sprW / 2 + spr->spriteScreenX;
	// if (spr->drawEndX >= settings->sW)
	// 	spr->drawEndX = settings->sW - 1;
	return(transformY);
}

void	setAndDraw(all_data *ever, sprite_data *listOfSprites, int i, settings *settings)
{
	player_data *pl;
	tex_data	*spr;
	double		transformY;//придётся оставить и передавать 

	spr = ever->sprite1;

	transformY = setParForSpr(ever, listOfSprites, i);
	drawSprite(ever, spr, settings, transformY);
}

void	sortDist2(all_data *ever, sprite_data *listOfSprites, settings *settings)
{
	int i;
	
	i = 0;
	while (i < ever->numOfSprite)
	{
		setAndDraw(ever, listOfSprites, i, settings);
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
	while(i < ever->numOfSprite)
	{
		while(j > i)
		{
			if(ever->spriteDist[j - 1] < ever->spriteDist[j])
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
	// printf("\nsorted spriteDist:\n");
	// for(int i = 0; i < ever->numOfSprite; i++)
	// {
	// printf("spriteDist[%d] = %f\n", i, ever->spriteDist[i]);
	// }
	// printf("\nsorted spriteOrder:\n");
	// for(int i = 0; i < ever->numOfSprite; i++)
	// {
	// printf("spriteOrder[%d] = %d\n", i, ever->spriteOrder[i]);
	// }
	sortDist2(ever,listOfSprites, settings);
	// i = 0;
	// while (i < ever->numOfSprite)
	// {
	// 	setWidthHeight(ever, listOfSprites, i, settings);
	// 	i++;
	// }
}

void	setAndSort(all_data *ever, sprite_data *listOfSprites, settings *settings)
{
	player_data *pl;
	int j;

	j = 0;
	pl = ever->player;
	//write(1, "Hello sort\n", 11);
	while (j < ever->numOfSprite)
	{
		ever->spriteOrder[j] = j;
		ever->spriteDist[j] = (pl->posX - listOfSprites[j].x) * 
			(pl->posX - listOfSprites[j].x) + (pl->posY - listOfSprites[j].y)
			* (pl->posY - listOfSprites[j].y);
		j++;
	}
	// for(int i = 0; i < ever->numOfSprite; i++)
	// {
	// 	printf("spriteOrder[%d] = %d\n", i, ever->spriteOrder[i]);
	// 	printf("spriteDist[%d] = %f\n", i, ever->spriteDist[i]);
	// }
	sortDist(ever, listOfSprites, settings);
}