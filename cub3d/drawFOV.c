#include "cub3d.h"

static void drawVertLine(all_data *everything, int x, settings *settings)
{
    int lineHeight;
    int drawStart;
    int drawEnd;
    int y;
    tex_data *temp;

    temp = everything->texture;
    y = 0;
    lineHeight = (int)(settings->sH / everything->raycasting->perpWallDist);

    //calculate lowest and highest pixel to fill in current stripe
    drawStart = -1 * lineHeight / 2 + settings->sH / 2;
    if(drawStart < 0)drawStart = 0;
    drawEnd = lineHeight / 2 + settings->sH / 2;
    if(drawEnd >= settings->sH)drawEnd = settings->sH - 1;

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
    double texPos = (drawStart - settings->sH / 2 + lineHeight / 2) * step;
    
    char *color;
    while (y < settings->sH)
    {
        if (y >= drawStart && y <= drawEnd)
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


