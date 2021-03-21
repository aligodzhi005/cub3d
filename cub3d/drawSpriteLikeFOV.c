/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawSpriteLikeFOV.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 14:28:07 by rvena             #+#    #+#             */
/*   Updated: 2021/03/19 14:30:04 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void    setBasSpritePar3(ray_data *raycasting, player_data *player, int worldMap[24][24], int x)
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
		if(worldMap[raycasting->mapY][raycasting->mapX] == 5) 
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

void    setBasSpritePar2(ray_data *raycasting, player_data *player, int worldMap[24][24], int x)
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
    setBasSpritePar3(raycasting, player, worldMap, x);
}



void    setBasSpritePar(ray_data *raycasting, player_data *player, int x, int worldMap[24][24])
{
    raycasting->cameraX = 2 * x / (double)screenWidth - 1; //x-coordinate in camera space
        raycasting->rayDirX = player->dirX + player->planeX * raycasting->cameraX;
        raycasting->rayDirY = player->dirY + player->planeY * raycasting->cameraX;
        

        raycasting->mapX = (int)player->posX;
        raycasting->mapY = (int)player->posY;

        // raycasting->deltaDistX = fabs(1 / raycasting->rayDirX);
        // raycasting->deltaDistY = fabs(1 / raycasting->rayDirY);
        raycasting->deltaDistX = (raycasting->rayDirY == 0) ? 0 : ((raycasting->rayDirX == 0) ? 1 : fabs(1 / raycasting->rayDirX));
        raycasting->deltaDistY = (raycasting->rayDirX == 0) ? 0 : ((raycasting->rayDirY == 0) ? 1 : fabs(1 / raycasting->rayDirY));
        raycasting->hit = 0;
        setBasSpritePar2(raycasting, player, worldMap, x);
}

static void drawVertSpriteLine(all_data *everything, int x)
{
    int lineHeight;
    int drawStart;
    int drawEnd;
    int y;
    tex_data *temp;

    temp = everything->texture;
    y = 0;
    lineHeight = (int)(screenHeight / everything->raycasting->perpWallDist);

    //calculate lowest and highest pixel to fill in current stripe
    drawStart = -1 * lineHeight / 2 + screenHeight / 2;
    if(drawStart < 0)drawStart = 0;
    drawEnd = lineHeight / 2 + screenHeight / 2;
    if(drawEnd >= screenHeight)drawEnd = screenHeight - 1;

    // double wallX; //where exactly the wall was hit
    // if(side == 0) wallX = posY + raycasting->perpWallDist * raycasting->rayDirX;
    // else          wallX = posX + perpWallDist * rayDirX;
    // wallX -= floor((wallX));

    //x coordinate on the texture
    int texX = (int)(everything->raycasting->wallX * (double)everything->texture->texWidth);
    if(everything->raycasting->side == 0 && everything->raycasting->rayDirX > 0) texX = everything->texture->texWidth - texX - 1;
    if(everything->raycasting->side == 1 && everything->raycasting->rayDirY < 0) texX = everything->texture->texWidth - texX - 1;

    // TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
    // How much to increase the texture coordinate per screen pixel
    double step = 1.0 * temp->texHeight / lineHeight;
    // Starting texture coordinate
    double texPos = (drawStart - screenHeight / 2 + lineHeight / 2) * step;
    
    char *color;
    while (y < screenHeight)
    {
        if (y > drawStart && y < drawEnd)
        {
            int texY = (int)texPos;
            // if(everything->raycasting->side == 0)//смотрим на запад или восток
            //     if(everything->raycasting->mapX < everything->player->posX)проверка на запад(если координата стены левее координаты персонажа по оси Х)
            //         my_mlx_pixel_put(everything->img, x, y, 0xF30BF3);
            //     else	если координата стены правее координаты персонажа по оси Х
            //         my_mlx_pixel_put(everything->img, x, y, 0x00FF0000);
            // else 
            //     //if
            //         my_mlx_pixel_put(everything->img, x, y, 0x990000);то же самое, только по Y
            
            texPos += step;
            color = everything->texture->addr + (texY * everything->texture->line_length + texX * (everything->texture->bits_per_pixel / 8));
            my_mlx_pixel_put(everything->img, x, y, *(int *)color);
        }
        else if (y < drawStart)
            my_mlx_pixel_put(everything->img, x, y, 0x0066CC);
        else if (y > drawEnd)
            my_mlx_pixel_put(everything->img, x, y, 0xCCFFF66);
        y++;
    }
}

void drawSprite(all_data *everything, int worldMap[24][24])
{
    int x;

	x = 0;
    while (x < screenWidth)
    {
        setBasSpritePar(everything->raycasting, everything->player, x, worldMap);
        drawSpriteVertLine(everything, x);
        x++;
    }
}