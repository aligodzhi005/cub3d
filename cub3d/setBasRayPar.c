/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setBasRayPar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 13:54:15 by rvena             #+#    #+#             */
/*   Updated: 2021/04/18 15:48:20 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	findWall(ray_data *raycasting, char **map)
{
	while (raycasting->hit == 0)
	{
		if (raycasting->sideDistX < raycasting->sideDistY)
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
		if (map[raycasting->mapY][raycasting->mapX] == '1')
			raycasting->hit = 1;
	}
}

static void	setBasRayPar3(ray_data *ray, player_data *player, char **map, int x)
{
	findWall(ray, map);
	if (ray->side == 0)
		ray->perpWallDist = (ray->mapX - player->posX + (1 - ray->stepX) / 2)
			/ ray->rayDirX;
	else
		ray->perpWallDist = (ray->mapY - player->posY + (1 - ray->stepY) / 2)
			/ ray->rayDirY;
	ray->Zbuffer[x] = ray->perpWallDist;
	if (ray->side == 0)
		ray->wallX = player->posY + ray->perpWallDist
			* ray->rayDirY;
	else
		ray->wallX = player->posX + ray->perpWallDist
			* ray->rayDirX;
	ray->wallX -= floor((ray->wallX));
}

void	setBasRayPar2(ray_data *ray, player_data *player, char **map, int x)
{
	if (ray->rayDirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (player->posX - ray->mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0 - player->posX) * ray->deltaDistX;
	}
	if (ray->rayDirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (player->posY - ray->mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - player->posY) * ray->deltaDistY;
	}
	setBasRayPar3(ray, player, map, x);
}

void	setBasRayPar(ray_data *ray, all_data *ever, int x, char **map)
{
	player_data	*player;
	settings	*settings;

	player = ever->player;
	settings = ever->settings;
	ray->cameraX = 2 * x / (double)settings->sW - 1;
	ray->rayDirX = player->dirX + player->planeX * ray->cameraX;
	ray->rayDirY = player->dirY + player->planeY * ray->cameraX;
	ray->mapX = (int)player->posX;
	ray->mapY = (int)player->posY;
	if (ray->rayDirY == 0)
		ray->deltaDistX = 0;
	else if (ray->rayDirX == 0)
		ray->deltaDistX = 1;
	else
		ray->deltaDistX = fabs(1 / ray->rayDirX);
	if (ray->rayDirX == 0)
		ray->deltaDistY = 0;
	else if (ray->rayDirY == 0)
		ray->deltaDistY = 1;
	else
		ray->deltaDistY = fabs(1 / ray->rayDirY);
	ray->hit = 0;
	setBasRayPar2(ray, player, map, x);
}
