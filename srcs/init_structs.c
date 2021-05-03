/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:32:24 by rvena             #+#    #+#             */
/*   Updated: 2021/04/21 22:00:45 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_settings	*init_t_settings(void)
{
	t_settings	*setting;

	setting = (t_settings *)malloc(sizeof(t_settings));
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
	return (setting);
}

t_plr_data	*init_player(void)
{
	t_plr_data	*player;

	player = (t_plr_data *)malloc(sizeof(t_plr_data));
	player->posX = 0;
	player->posY = 0;
	player->dirX = 0;
	player->dirY = 0;
	player->planeX = 0;
	player->planeY = 0;
	player->rotSpeed = 0.09;
	player->moveSpeed = 2;
	player->rR = 0;
	player->rL = 0;
	player->mB = 0;
	player->mF = 0;
	player->mL = 0;
	player->mR = 0;
	return (player);
}

void	init_path_mas(t_settings *t_settings)
{
	t_settings->path_mas = (char **)malloc(sizeof(char *) * 4);
	t_settings->path_mas[0] = t_settings->NO;
	t_settings->path_mas[1] = t_settings->SO;
	t_settings->path_mas[2] = t_settings->WE;
	t_settings->path_mas[3] = t_settings->EA;
}

void	init_text(t_all_data	*everything)
{
	t_tex_data	*mas;
	t_settings	*set;
	t_data		*tmp_img;
	int			i;

	i = 0;
	everything->tex_mas = (t_tex_data *)malloc(sizeof(t_tex_data) * 4);
	mas = everything->tex_mas;
	set = everything->t_settings;
	tmp_img = everything->img;
	init_path_mas(set);
	while (i < 4)
	{
		mas[i].ind = mlx_png_file_to_image(tmp_img->mlx_ptr, set->path_mas[i],
				&mas[i].texWidth, &mas[i].texHeight);
		if (mas[i].ind == 0)
		{
			printf("Error\nBad photo for texture\nTry another phoro\n");
			exit(-1);
		}
		mas[i].addr = mlx_get_data_addr(mas[i].ind, &mas[i].bits_per_pixel,
				&mas[i].line_length, &mas[i].endian);
		i++;
	}
}

t_data	*initImgStr(t_settings	*t_settings)
{
	t_data	*img;

	img = (t_data *)malloc(sizeof(t_data));
	if (img == NULL)
	{
		printf("Error\nError malloc img\n");
		exit(-1);
	}
	mlx_get_screen_size(img->mlx_ptr,
		&t_settings->pcscrW, &t_settings->pcscrH);
	if (t_settings->sW > t_settings->pcscrW)
		t_settings->sW = t_settings->pcscrW;
	if (t_settings->sH > t_settings->pcscrH)
		t_settings->sH = t_settings->pcscrH;
	img->mlx_ptr = mlx_init();
	img->win_ptr = mlx_new_window(img->mlx_ptr, t_settings->sW,
			t_settings->sH, "Raycasting");
	img->ind = mlx_new_image(img->mlx_ptr, t_settings->sW, t_settings->sH);
	img->addr = mlx_get_data_addr(img->ind, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	return (img);
}
