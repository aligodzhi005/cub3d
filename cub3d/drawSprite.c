/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawSprite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:20:27 by rvena             #+#    #+#             */
/*   Updated: 2021/04/17 16:45:14 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	setWidthHeight(all_data *ever, sprite_data *listOfSprites, int i, settings *settings)
{
	player_data *pl;
	tex_data	*spr;
	tex_data	*tex1;
	double		spriteX;
	double		spriteY;
	double		invDet;
	double		transformX;
	double		transformY;
	int			spriteScreenX;
	int			spriteHeight;
	int			drawStartY;
	int			drawEndY;
	int			spriteWidth;
	int			drawStartX;
	int			drawEndX;

	pl = ever->player;
	spr = ever->sprite1;

	// printf("listOfSprites[ever->spriteOrder[i]].x = %f\n", listOfSprites[ever->spriteOrder[i]].x);//в этом месте сегается
	// printf("pl->posX = %f\n", pl->posX);
	spriteX = listOfSprites[ever->spriteOrder[i]].x - pl->posX;
	spriteY = listOfSprites[ever->spriteOrder[i]].y - pl->posY;

	invDet = 1 / (pl->planeX * pl->dirY - pl->dirX * pl->planeY);

	transformX = invDet * (pl->dirY * spriteX - pl->dirX * spriteY);
	transformY = invDet * (-1 * pl->planeY * spriteX + pl->planeX * spriteY);
	
	spriteScreenX = (int)((settings->sW / 2) * (1 + transformX / transformY));
	spriteHeight = abs((int)(settings->sH / transformY));
	
	drawStartY = -1 * spriteHeight / 2 + settings->sH / 2;
	if(drawStartY < 0)
		drawStartY = 0;
	drawEndY = spriteHeight / 2 + settings->sH / 2;
	if (drawEndY >= settings->sH)
		drawEndY = settings->sH - 1;
	
	spriteWidth = abs((int)(settings->sW / (transformY)));
	drawStartX = -1 * spriteWidth / 2 + spriteScreenX;
	if (drawStartX < 0)
		drawStartX = 0;
	drawEndX = spriteWidth / 2 + spriteScreenX;
	if (drawEndX >= settings->sW)
		drawEndX = settings->sW - 1;

	//Draw Sprite
	//printf("\nDraw Sprite\n");
	int sprite;
	int y;
	char *color;
	
	sprite = drawStartX;
	while (sprite < drawEndX)
	{
		//printf("sprite = %d\n", sprite);
		int texX = (int)(256 * (sprite - (-1 * spriteWidth / 2 + spriteScreenX)) * ever->sprite1->texWidth / spriteWidth) / 256;
		y = drawStartY;
		if(transformY > 0 && sprite < settings->sW && transformY < ever->raycasting->Zbuffer[sprite])
		while (y < drawEndY)
		{
			//printf("y = %d\n", y);
			int d = y * 256 - settings->sH * 128 + spriteHeight * 128;
			int texY = ((d * spr->texHeight) / spriteHeight) / 256;
			color = spr->addr + (texY * spr->line_length + texX * (spr->bits_per_pixel / 8));
			//printf("color = %d\n", *(int *)color);
			if(*(int *)color != 0)
				my_mlx_pixel_put(ever->img, sprite, y, *(int *)color);
			y++;
		}
		sprite++;
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
	i = 0;
	while (i < ever->numOfSprite)
	{
		setWidthHeight(ever, listOfSprites, i, settings);
		i++;
	}
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