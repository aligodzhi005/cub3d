/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setBasRayPar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 13:54:15 by rvena             #+#    #+#             */
/*   Updated: 2021/03/21 16:46:12 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    setBasRayPar3(ray_data *raycasting, player_data *player, char **map, int x)
{
	 //where exactly the wall was hit
	while (raycasting->hit == 0)
	{
		//jump to next map square, OR in x-direction, OR in y-direction
		if(raycasting->sideDistX < raycasting->sideDistY)
		{
			raycasting->sideDistX += raycasting->deltaDistX;
			raycasting->mapX += raycasting->stepX;
			raycasting->side = 0;
		}
		else
		{
			raycasting->sideDistY += raycasting->deltaDistY;
			raycasting->mapY += raycasting->stepY;
			raycasting->side = 1;
		}
		if(map[raycasting->mapY][raycasting->mapX] == '1') 
			raycasting->hit = 1;
    }
    //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
    if(raycasting->side == 0) 
        raycasting->perpWallDist = (raycasting->mapX - player->posX + (1 - raycasting->stepX) / 2) / raycasting->rayDirX;
    else          
        raycasting->perpWallDist = (raycasting->mapY - player->posY + (1 - raycasting->stepY) / 2) / raycasting->rayDirY;
	raycasting->Zbuffer[x] = raycasting->perpWallDist;
    //printf("raycasting->rayDirY = %f\n", raycasting->rayDirY);
	//printf("raycasting->perpWallDist = %f\n", raycasting->perpWallDist);
    if(raycasting->side == 0) 
        raycasting->wallX = player->posY + raycasting->perpWallDist * raycasting->rayDirY;
    else          
        raycasting->wallX = player->posX + raycasting->perpWallDist * raycasting->rayDirX;
    raycasting->wallX -= floor((raycasting->wallX));
    //printf("mapX = %d\nmapY = %d\n", raycasting->mapX, raycasting->mapY);
}

void    setBasRayPar2(ray_data *raycasting, player_data *player, char **map, int x, settings *settings)
{
    if(raycasting->rayDirX < 0)
    {
        raycasting->stepX = -1;
        raycasting->sideDistX = (player->posX - raycasting->mapX) * raycasting->deltaDistX;
    }
    else
    {
        raycasting->stepX = 1;
        raycasting->sideDistX = (raycasting->mapX + 1.0 - player->posX) * raycasting->deltaDistX;
    }
    if(raycasting->rayDirY < 0)
    {
        raycasting->stepY = -1;
        raycasting->sideDistY = (player->posY - raycasting->mapY) * raycasting->deltaDistY;
    }
    else
    {
        raycasting->stepY = 1;
        raycasting->sideDistY = (raycasting->mapY + 1.0 - player->posY) * raycasting->deltaDistY;
    }
    setBasRayPar3(raycasting, player, map, x);
}



void    setBasRayPar(ray_data *raycasting, player_data *player, int x, char **map, settings *settings)
{
    raycasting->cameraX = 2 * x / (double)settings->sW - 1; //x-coordinate in camera space
    raycasting->rayDirX = player->dirX + player->planeX * raycasting->cameraX;
    raycasting->rayDirY = player->dirY + player->planeY * raycasting->cameraX;
    
	raycasting->mapX = (int)player->posX;
	raycasting->mapY = (int)player->posY;
	// raycasting->deltaDistX = fabs(1 / raycasting->rayDirX);
	// raycasting->deltaDistY = fabs(1 / raycasting->rayDirY);
	raycasting->deltaDistX = (raycasting->rayDirY == 0) ? 0 : ((raycasting->rayDirX == 0) ? 1 : fabs(1 / raycasting->rayDirX));
	raycasting->deltaDistY = (raycasting->rayDirX == 0) ? 0 : ((raycasting->rayDirY == 0) ? 1 : fabs(1 / raycasting->rayDirY));
	raycasting->hit = 0;
	setBasRayPar2(raycasting, player, map, x, settings);
}