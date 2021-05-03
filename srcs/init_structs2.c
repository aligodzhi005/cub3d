/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 21:04:03 by rvena             #+#    #+#             */
/*   Updated: 2021/04/21 22:00:43 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_tex_data	*initSpr(t_all_data	*everything)
{
	t_tex_data	*sprite1;

	sprite1 = (t_tex_data *)malloc(sizeof(t_tex_data));
	if (sprite1 == NULL)
	{
		printf("Error\nError malloc sprite\n");
		exit(-1);
	}
	sprite1->ind = mlx_png_file_to_image(everything->img->mlx_ptr,
			everything->t_settings->S, &sprite1->texWidth, &sprite1->texHeight);
	sprite1->addr = mlx_get_data_addr(sprite1->ind, &sprite1->bits_per_pixel,
			&sprite1->line_length, &sprite1->endian);
	return (sprite1);
}

void	initEverything1(t_all_data *everything)
{
	t_ray_data	*raycasting;

	raycasting = (t_ray_data *)malloc(sizeof(t_ray_data));
	everything->listOfSprites = NULL;
	everything->raycasting = raycasting;
	everything->numOfSprite = 0;
	everything->t_settings = init_t_settings();
	everything->screenshot = 0;
	everything->player = init_player();
}

void	initEverything2(t_all_data *ever)
{
	ever->raycasting->Zbuffer = (double *)malloc(sizeof(double)
			* ever->t_settings->sW);
	ever->img = initImgStr(ever->t_settings);
	init_text(ever);
}
