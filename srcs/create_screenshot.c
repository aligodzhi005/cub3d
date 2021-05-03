/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_screenshot.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 20:44:12 by rvena             #+#    #+#             */
/*   Updated: 2021/04/21 21:33:28 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	create_screenshot2(int fd, t_all_data *everything)
{
	int32_t	x;
	int32_t	y;
	int		color;

	y = everything->t_settings->sH - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < everything->t_settings->sW)
		{
			color = *(unsigned int *)(everything->img->addr
					+ (y * everything->img->line_length)
					+ x * (everything->img->bits_per_pixel / 8));
			write(fd, &color, 4);
			x++;
		}
		y--;
	}
	close(fd);
}

void	create_screenshot(t_all_data *everything)
{
	int		fd;
	char	bitmap[54];

	fd = 0;
	fd = open("screenshot.bmp", O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	if (fd < 0)
	{
		printf("Error\nСreating a screenshot resulted in an error");
		exit(-1);
	}
	ft_bzero(bitmap, 54);
	bitmap[0] = 'B';
	bitmap[1] = 'M';
	*((int *)(bitmap + 2)) = everything->t_settings->sH
		* everything->t_settings->sW * 4 + 54;
	*(int *)(bitmap + 10) = 54;
	*(int *)(bitmap + 14) = 40;
	*(int *)(bitmap + 18) = everything->t_settings->sW;
	*(int *)(bitmap + 22) = everything->t_settings->sH;
	*(bitmap + 26) = 1;
	*(bitmap + 28) = 32;
	write(fd, bitmap, 54);
	create_screenshot2(fd, everything);
}
