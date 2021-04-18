/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxFunctions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:34:28 by rvena             #+#    #+#             */
/*   Updated: 2021/04/18 14:51:03 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void		rotation(player_data *player, char **map, t_data *minimap, int i)
{
	double oldDirX;
	double oldPlaneX;

	oldDirX = player->dirX;
	player->dirX = player->dirX * cos(i * (player->rotSpeed) * 0.5) - player->dirY * sin(i * (player->rotSpeed) * 0.5);
	player->dirY = oldDirX * sin(i * (player->rotSpeed) * 0.5) + player->dirY * cos(i * (player->rotSpeed) * 0.5);
	oldPlaneX = player->planeX;
	player->planeX = player->planeX * cos(i * (player->rotSpeed) * 0.5) - player->planeY * sin(i * (player->rotSpeed) * 0.5);
	player->planeY = oldPlaneX * sin(i * (player->rotSpeed) * 0.5) + player->planeY * cos(i * (player->rotSpeed) * 0.5);
}
static void		movement2(player_data *player, char **map, t_data *minimap)
{
	if(player->mR == 1)
	{
		// put_square(*minimap, 2, (int)player->posX, (int)player->posY, 10);
		// mlx_put_image_to_window(minimap->mlx_ptr, minimap->win_ptr, minimap->ind, 0, 0);
		if(map[(int)((player->posY + player->planeY * 0.5))][(int)(player->posX)] == '0')    
                player->posY += player->planeY * player->moveSpeed * 0.1;
		if(map[(int)(player->posY)][(int)((player->posX + player->planeX * 0.5)) ] == '0')
				player->posX += player->planeX * player->moveSpeed * 0.1;
	}
	if(player->rR == 1)
		rotation(player, map, minimap, 1);
	if(player->rL == 1)
		rotation(player, map, minimap, -1);
}

int				movement(player_data *player, char **map, t_data *minimap)
{
	// printf("old posY = %f\nold posX = %f\n", player->posY, player->posX);
	// put_square(*minimap, 2, (int)player->posX, (int)player->posY, 10);
	// mlx_put_image_to_window(minimap->mlx_ptr, minimap->win_ptr, minimap->ind, 0, 0);
	if(player->mF == 1)
	{
		// put_square(*minimap, 2, (int)player->posX, (int)player->posY, 10);
		// mlx_put_image_to_window(minimap->mlx_ptr, minimap->win_ptr, minimap->ind, 0, 0);
		if(map[(int)((player->posY + player->dirY * 0.5))][(int)(player->posX)] == '0')    
				player->posY += player->dirY * player->moveSpeed * 0.1;
		if(map[(int)(player->posY)][(int)((player->posX + player->dirX * 0.5)) ] == '0')
				player->posX += player->dirX * player->moveSpeed * 0.1;
	}
	if(player->mB == 1)
	{
		// put_square(*minimap, 2, (int)player->posX, (int)player->posY, 10);
		// mlx_put_image_to_window(minimap->mlx_ptr, minimap->win_ptr, minimap->ind, 0, 0);
		if(map[(int)((player->posY - player->dirY * player->moveSpeed* 0.5))][(int)(player->posX)] == '0')
				player->posY -= player->dirY * player->moveSpeed * 0.1;
		if(map[(int)(player->posY)][(int)((player->posX - player->dirX * player->moveSpeed* 0.5) )] == '0')
				player->posX -= player->dirX * player->moveSpeed * 0.1;
	}
	if(player->mL == 1)
	{
		// put_square(*minimap, 2, (int)player->posX, (int)player->posY, 10);
		// mlx_put_image_to_window(minimap->mlx_ptr, minimap->win_ptr, minimap->ind, 0, 0);
		if(map[(int)((player->posY - player->planeY * 0.5))][(int)(player->posX)] == '0')    
                player->posY -= player->planeY * player->moveSpeed * 0.1;
        if(map[(int)(player->posY)][(int)((player->posX - player->planeX * 0.5)) ] == '0')
                player->posX -= player->planeX * player->moveSpeed * 0.1;
	}//21
	movement2(player, map, minimap);
	return(0);
}

int 	render_next_frame(all_data *everything)
{
	// printf("Privet Kuk");
	mlx_clear_window(everything->img->mlx_ptr, everything->img->win_ptr);
    // mlx_clear_window(everything->minimap->mlx_ptr, everything->minimap->win_ptr);
	// put_square(*everything->minimap, 2, (int)everything->player->posX, (int)everything->player->posY, 10);
	// mlx_put_image_to_window(everything->minimap->mlx_ptr, everything->minimap->win_ptr, everything->minimap->ind, 0, 0);
	movement(everything->player, everything->map, everything->minimap);
	printf("Бляяяяяяяя\n");
    drawFOV(everything, everything->map, everything->settings);
	printf("Ты где тварь\n");
	setAndSort(everything, everything->listOfSprites, everything->settings);
	printf("Я тебя чую\n");
	// put_square(*everything->minimap, 1, (int)everything->player->posX, (int)everything->player->posY, 10);
	// mlx_put_image_to_window(everything->minimap->mlx_ptr, everything->minimap->win_ptr, everything->minimap->ind, 0, 0);

	mlx_put_image_to_window(everything->img->mlx_ptr, everything->img->win_ptr, everything->img->ind, 0, 0);
	// printf("screenshot = %d", everything->screenshot);
	
	if(everything->screenshot == 1)
		create_screenshot(everything);
	mlx_do_sync(everything->img->mlx_ptr);
	// mlx_loop(everything->img->mlx_ptr);
	return (0);
}

int		key_hook_release(int keycode, player_data *player)
{
	if(keycode == 13)
		player->mF = 0;
	if(keycode == 1)
		player->mB = 0;
	if(keycode == 0)
		player->mL = 0;
	if(keycode == 2)
		player->mR = 0;
	if (keycode == 123)
		player->rL = 0;
	if(keycode == 124)
		player->rR = 0;
	// printf("it works\n");
	return (0);
}

int		finish_game(all_data *everything)
{
	mlx_destroy_window(everything->img->mlx_ptr, everything->img->win_ptr);
	exit(-1);
	return(1);
}

int		key_hook(int keycode, player_data *player)
{
	// put_square(*minimap, 2, (int)player->posX, (int)player->posY, 10);
	// mlx_put_image_to_window(minimap->mlx_ptr, minimap->win_ptr, minimap->ind, 0, 0);
	if (keycode == 124)
		player->rR = 1;
	if (keycode == 123)
		player->rL = 1;
    if (keycode == 13)
		player->mF = 1;
    if (keycode == 1)
		player->mB = 1;
	if (keycode == 0)
		player->mL = 1;
	if (keycode == 2)
		player->mR = 1;
	if (keycode == 53)
		exit(1);
	// printf("%i\n", keycode);
	return(0);
}