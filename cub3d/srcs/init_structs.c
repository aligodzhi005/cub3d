/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:32:24 by rvena             #+#    #+#             */
/*   Updated: 2021/04/17 21:26:58 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

settings *init_settings(void)
{
	settings	*setting;
	
	setting = (settings *)malloc(sizeof(settings));
	setting->sW = 0;
	setting->sH = 0;
	setting->NO = NULL;
	setting->SO = NULL;
	setting->WE = NULL;
	setting->EA = NULL;
	setting->S = NULL;
	setting->floor = -1;
	setting->ceilling = -1;
	setting->mapH = 0;
	setting->mapW = 0;
	setting->pcscrH = 0;
	setting->pcscrW = 0;
	return(setting);
}

player_data *init_player(void)
{
	player_data *player;
	
	player = (player_data *)malloc(sizeof(player_data));
	player->posX = 0;
	player->posY = 0;
	player->dirX = 0;
	player->dirY = 0;
	player->planeX = 0;
	player->planeY = 0;
	player->rotSpeed = 0.09;
	player->moveSpeed = 1;
	player->rR = 0;
	player->rL = 0;
	player->mB = 0;
	player->mF = 0;
	player->mL = 0;
	player->mR = 0;
	return(player);
}

void	init_path_mas(settings *settings)
{
	settings->path_mas = (char **)malloc(sizeof(char *) * 4);
	settings->path_mas[0] = settings->NO;
	settings->path_mas[1] = settings->SO;
	settings->path_mas[2] = settings->WE;
	settings->path_mas[3] = settings->EA;
}

void	init_text(all_data	*everything)
{
	// tex_data	*texture1;
	// tex_data	*texture2;
	// tex_data	*texture3;
	// tex_data	*texture4;
	tex_data	*tmp_texmas;
	settings	*tmp_settings;
	t_data		*tmp_img;
	int i;

	i = 0;
	everything->tex_mas = (tex_data *)malloc(sizeof(tex_data) * 4);
	// while(i < 4)
	// 	everything->tex_mas[i++] = (tex_data *)malloc(sizeof(tex_data));
	tmp_texmas = everything->tex_mas;
	tmp_settings = everything->settings;
	tmp_img = everything->img;
	init_path_mas(tmp_settings);
	while(i < 4)
	{
		tmp_texmas[i].ind = mlx_png_file_to_image(tmp_img->mlx_ptr, tmp_settings->path_mas[i], 
			&tmp_texmas[i].texWidth, &tmp_texmas[i].texHeight);
		if(tmp_texmas[i].ind == 0)
		{
			printf("Error\nBad photo for texture\nTry another phoro\n");
			exit(-1);
		}
		tmp_texmas[i].addr = mlx_get_data_addr(tmp_texmas[i].ind, &tmp_texmas[i].bits_per_pixel, 
			&tmp_texmas[i].line_length, &tmp_texmas[i].endian);
		i++;
	}
	// texture1 = (tex_data *)malloc(sizeof(tex_data));
	// texture2 = (tex_data *)malloc(sizeof(tex_data));
	// texture3 = (tex_data *)malloc(sizeof(tex_data));
	// texture4 = (tex_data *)malloc(sizeof(tex_data));
	// everything->texture = texture1;
	// everything->texture2 = texture2;
	// everything->texture3 = texture3;
	// everything->texture4 = texture4;
	// texture1.ind = mlx_png_file_to_image(img.mlx_ptr, everything.settings->NO, &texture1.texWidth, &texture1.texHeight);
    // texture1.addr = mlx_get_data_addr(texture1.ind, &texture1.bits_per_pixel, 
    //                                 &texture1.line_length, &texture1.endian);
	// texture2.ind = mlx_png_file_to_image(img.mlx_ptr, everything.settings->SO, &texture2.texWidth, &texture2.texHeight);
    // texture2.addr = mlx_get_data_addr(texture2.ind, &texture2.bits_per_pixel, 
    //                                 &texture2.line_length, &texture2.endian);
	// texture3.ind = mlx_png_file_to_image(img.mlx_ptr, everything.settings->EA, &texture3.texWidth, &texture3.texHeight);
    // texture3.addr = mlx_get_data_addr(texture3.ind, &texture3.bits_per_pixel, 
    //                                 &texture3.line_length, &texture3.endian);
	// texture4.ind = mlx_png_file_to_image(img.mlx_ptr, everything.settings->WE, &texture4.texWidth, &texture4.texHeight);
    // texture4.addr = mlx_get_data_addr(texture4.ind, &texture4.bits_per_pixel, 
    //                                 &texture4.line_length, &texture4.endian);
}

t_data *initImgStr(settings	*settings)
{
	t_data *img;

	img = (t_data *)malloc(sizeof(t_data));
	if(img == NULL)
	{
		printf("Error\nError malloc img\n");
		exit(-1);
	}
	img->mlx_ptr = mlx_init();
    img->win_ptr = mlx_new_window(img->mlx_ptr, settings->sW, settings->sH, "Raycasting");
	img->ind = mlx_new_image(img->mlx_ptr, settings->sW, settings->sH);
	img->addr = mlx_get_data_addr(img->ind, &img->bits_per_pixel, &img->line_length,
									&img->endian);
	return(img);
}

tex_data	*initSpr(all_data	*everything)
{
	tex_data *sprite1;

	sprite1 = (tex_data *)malloc(sizeof(tex_data));
	if(sprite1 == NULL)
	{
		printf("Error\nError malloc sprite\n");
		exit(-1);
	}
	sprite1->ind = mlx_png_file_to_image(everything->img->mlx_ptr, everything->settings->S, &sprite1->texWidth, &sprite1->texHeight);
	sprite1->addr = mlx_get_data_addr(sprite1->ind, &sprite1->bits_per_pixel, 
									&sprite1->line_length, &sprite1->endian);
	return(sprite1);
}