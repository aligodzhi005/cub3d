/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setListOfSprite.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 20:51:52 by rvena             #+#    #+#             */
/*   Updated: 2021/04/22 14:14:20 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	mallocListOfSprites(t_all_data *everything, t_sprite_data *tmp)
{
	everything->listOfSprites = (t_sprite_data *)malloc(sizeof(t_sprite_data)
			* (everything->numOfSprite));
	if (everything->listOfSprites == NULL)
	{
		printf("Error\nMalloc listOfSprites error\n");
		free(tmp);
		exit(-1);
	}
}

void	setListOfSprite(t_all_data *everything, int i, int j)
{
	t_sprite_data	*tmp;
	int				l;

	l = 0;
	everything->numOfSprite++;
	tmp = everything->listOfSprites;
	mallocListOfSprites(everything, tmp);
	while (l < everything->numOfSprite - 1)
	{
		everything->listOfSprites[l].x = tmp[l].x;
		everything->listOfSprites[l].y = tmp[l].y;
		l++;
	}
	everything->listOfSprites[everything->numOfSprite - 1].x = j + 0.5;
	everything->listOfSprites[everything->numOfSprite - 1].y = i + 0.5;
	free(tmp);
}
