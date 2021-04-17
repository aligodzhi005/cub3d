/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawFOV.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 14:12:52 by rvena             #+#    #+#             */
/*   Updated: 2021/04/17 17:45:16 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static void drawPixel()
static int setTexX(all_data *everything, tex_data *temp)
{
	int texX;

	texX = (int)(everything->raycasting->wallX * (double)temp->texWidth);
	if(everything->raycasting->side == 0 && everything->raycasting->rayDirX > 0)
		texX = temp->texWidth - texX - 1;
	if(everything->raycasting->side == 1 && everything->raycasting->rayDirY < 0)
		texX = temp->texWidth - texX - 1;
	return(texX);
}

static void drawFloorCeil(tex_data *temp, all_data *everything, int x, int y)
{
	if (y < temp->drawStart)
		my_mlx_pixel_put(everything->img, x, y, everything->settings->ceilling);
	else if (y > temp->drawEnd)
		my_mlx_pixel_put(everything->img, x, y, everything->settings->floor);
}

static void drawVertLine2(tex_data *temp, all_data *everything, int lineHeight, int x)
{
	int		texX;
	double	step;
	double	texPos;
	char	*color;
	int		y;
	int		texY;

	y = 0;
	// printf("TUT!\n");
	texX = setTexX(everything, temp);
	// texX = (int)(everything->raycasting->wallX * (double)temp->texWidth);
	// if(everything->raycasting->side == 0 && everything->raycasting->rayDirX > 0)
	// 	texX = temp->texWidth - texX - 1;
	// if(everything->raycasting->side == 1 && everything->raycasting->rayDirY < 0)
	// 	texX = temp->texWidth - texX - 1;
	// printf("drawStart = %d\ndrawEnd = %d\n", temp->drawStart, temp->drawEnd);
    // TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
    // How much to increase the texture coordinate per screen pixel
	step = 1.0 * temp->texHeight / lineHeight;
    // Starting texture coordinate
	texPos = (temp->drawStart - everything->settings->sH / 2 + lineHeight / 2) * step;
	while (y < everything->settings->sH)
	{
		// printf("пидор y = %d settings->sH = %d\n", y, settings->sH);
		if (y >= temp->drawStart && y <= temp->drawEnd)
		{
			texY = (int)texPos;
			texPos += step;
			color = temp->addr + (texY * temp->line_length + texX * (temp->bits_per_pixel / 8));
			my_mlx_pixel_put(everything->img, x, y, *(int *)color);
		}
		drawFloorCeil(temp, everything, x, y);
		// else if (y < temp->drawStart)
		// 	my_mlx_pixel_put(everything->img, x, y, everything->settings->ceilling);
		// else if (y > temp->drawEnd)
		// 	my_mlx_pixel_put(everything->img, x, y, everything->settings->floor);
		y++;
	}
}

static tex_data *chooseTex(all_data *everything)
{
	tex_data *temp;
	if(everything->raycasting->side == 0)//смотрим на запад или восток
		if(everything->raycasting->mapX < everything->player->posX)//проверка на запад(если координата стены левее координаты персонажа по оси Х)
			temp = &everything->tex_mas[3];
		else	//если координата стены правее координаты персонажа по оси Х
			temp = &everything->tex_mas[2];
	else
		if(everything->raycasting->mapY < everything->player->posY)
			temp = &everything->tex_mas[1];
		else
			temp = &everything->tex_mas[0];
	return(temp);
}

static void drawVertLine(all_data *everything, int x, settings *settings)
{
    int lineHeight;
    // int drawStart;
    // int drawEnd;
    tex_data *temp;

	temp = chooseTex(everything);
	// temp->drawStart = 0;
	// temp->drawEnd = 0;
    lineHeight = (int)(settings->sH / everything->raycasting->perpWallDist);
    //calculate lowest and highest pixel to fill in current stripe
	temp->drawStart = -1 * lineHeight / 2 + settings->sH / 2;
	if(temp->drawStart < 0)
		temp->drawStart = 0;
	temp->drawEnd = lineHeight / 2 + settings->sH / 2;
    if(temp->drawEnd >= settings->sH)
		temp->drawEnd = settings->sH - 1;
	everything->texture = temp;
    // double wallX; //where exactly the wall was hit
    // if(side == 0) wallX = posY + raycasting->perpWallDist * raycasting->rayDirX;
    // else          wallX = posX + perpWallDist * rayDirX;
    // wallX -= floor((wallX));

    //x coordinate on the texture
	drawVertLine2(temp, everything, lineHeight, x);
	// int		texX;
	// double	step;
	// double	texPos;
	// char	*color;
	// int		y;
	// int		texY;

	// y = 0;
	// // printf("TUT!\n");
	// texX = (int)(everything->raycasting->wallX * (double)temp->texWidth);
	// if(everything->raycasting->side == 0 && everything->raycasting->rayDirX > 0)
	// 	texX = temp->texWidth - texX - 1;
	// if(everything->raycasting->side == 1 && everything->raycasting->rayDirY < 0)
	// 	texX = temp->texWidth - texX - 1;
	// // printf("drawStart = %d\ndrawEnd = %d\n", temp->drawStart, temp->drawEnd);
    // // TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
    // // How much to increase the texture coordinate per screen pixel
	// step = 1.0 * temp->texHeight / lineHeight;
    // // Starting texture coordinate
	// texPos = (temp->drawStart - settings->sH / 2 + lineHeight / 2) * step;
	// while (y < settings->sH)
	// {
	// 	// printf("пидор y = %d settings->sH = %d\n", y, settings->sH);
	// 	if (y >= temp->drawStart && y <= temp->drawEnd)
	// 	{
	// 		texY = (int)texPos;
	// 		texPos += step;
	// 		color = temp->addr + (texY * temp->line_length + texX * (temp->bits_per_pixel / 8));
	// 		my_mlx_pixel_put(everything->img, x, y, *(int *)color);
	// 	}
	// 	else if (y < temp->drawStart)
	// 		my_mlx_pixel_put(everything->img, x, y, settings->ceilling);
	// 	else if (y > temp->drawEnd)
	// 		my_mlx_pixel_put(everything->img, x, y, settings->floor);
	// 	y++;
	// }
}

void drawFOV(all_data *everything, char **map, settings *settings)
{
    int x;

	x = 0;
    while (x < settings->sW)
    {
        setBasRayPar(everything->raycasting, everything->player, x, map, settings);
        drawVertLine(everything, x, settings);
        x++;
    }
}


