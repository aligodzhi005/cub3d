/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_dir_plane.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:21:16 by rvena             #+#    #+#             */
/*   Updated: 2021/04/21 21:37:14 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	setDirPlane2(char way, t_plr_data *player)
{
	if (way == 'E')
	{
		player->dirX = 1;
		player->dirY = 0;
		player->planeX = 0;
		player->planeY = 0.66;
	}
	else if (way == 'W')
	{
		player->dirX = -1;
		player->dirY = 0;
		player->planeX = 0;
		player->planeY = -0.66;
	}
}

void	setDirPlane(char way, t_plr_data *player)
{
	if (way == 'N')
	{
		player->dirX = 0;
		player->dirY = -1;
		player->planeX = 0.66;
		player->planeY = 0;
	}
	else if (way == 'S')
	{
		player->dirX = 0;
		player->dirY = 1;
		player->planeX = -0.66;
		player->planeY = 0;
	}
	setDirPlane2(way, player);
}
