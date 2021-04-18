/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxFunctions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:34:28 by rvena             #+#    #+#             */
/*   Updated: 2021/04/18 20:08:31 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	rotation(player_data *player, char **map,
				t_data *minimap, int i)
{
	double	oldDirX;
	double	oldPlaneX;

	oldDirX = player->dirX;
	player->dirX = player->dirX * cos(i * (player->rotSpeed) * 0.5)
		- player->dirY * sin(i * (player->rotSpeed) * 0.5);
	player->dirY = oldDirX * sin(i * (player->rotSpeed) * 0.5)
		+ player->dirY * cos(i * (player->rotSpeed) * 0.5);
	oldPlaneX = player->planeX;
	player->planeX = player->planeX * cos(i * (player->rotSpeed) * 0.5)
		- player->planeY * sin(i * (player->rotSpeed) * 0.5);
	player->planeY = oldPlaneX * sin(i * (player->rotSpeed) * 0.5)
		+ player->planeY * cos(i * (player->rotSpeed) * 0.5);
}

int	render_next_frame(all_data *everything)
{
	mlx_clear_window(everything->img->mlx_ptr, everything->img->win_ptr);
	movement(everything->player, everything->map, everything->minimap);
	drawFOV(everything, everything->map, everything->settings);
	setAndSort(everything, everything->listOfSprites, everything->settings);
	mlx_put_image_to_window(everything->img->mlx_ptr,
		everything->img->win_ptr, everything->img->ind, 0, 0);
	if (everything->screenshot == 1)
		create_screenshot(everything);
	mlx_do_sync(everything->img->mlx_ptr);
	return (0);
}

int	key_hook_release(int keycode, player_data *player)
{
	if (keycode == 13)
		player->mF = 0;
	if (keycode == 1)
		player->mB = 0;
	if (keycode == 0)
		player->mL = 0;
	if (keycode == 2)
		player->mR = 0;
	if (keycode == 123)
		player->rL = 0;
	if (keycode == 124)
		player->rR = 0;
	return (0);
}

int	finish_game(all_data *everything)
{
	mlx_destroy_window(everything->img->mlx_ptr, everything->img->win_ptr);
	exit(-1);
	return (1);
}

int	key_hook(int keycode, player_data *player)
{
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
	return (0);
}
