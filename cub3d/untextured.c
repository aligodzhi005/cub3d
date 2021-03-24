/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   untextured.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 11:16:20 by rvena             #+#    #+#             */
/*   Updated: 2021/03/21 17:15:44 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			put_square(t_data img, int col, int x, int y, int scale)
{
	int i;
	int j;

	x *= scale;
	y *= scale;

	i = x;
	j = y;

	while(j < y + scale)
	{
		i = x;
		while(i < x + scale)
		{
			if(col == 0)
				my_mlx_pixel_put(&img, i, j, 0xFFFFFF);
			else if(col == 1)
				my_mlx_pixel_put(&img, i, j, 0x0000FF00);
			else if(col == 2)
				my_mlx_pixel_put(&img, i, j, 0x000000);
			i++;
		}
		j++;
	}
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
		if(map[(int)((player->posY - player->dirY * player->moveSpeed* 0.5) )][(int)(player->posX)] == '0')
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
	}
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
	{
		double oldDirX = player->dirX;
        player->dirX = player->dirX * cos((player->rotSpeed) * 0.5) - player->dirY * sin((player->rotSpeed) * 0.5);
        player->dirY = oldDirX * sin((player->rotSpeed) * 0.5) + player->dirY * cos((player->rotSpeed) * 0.5);
        double oldPlaneX = player->planeX;
        player->planeX = player->planeX * cos((player->rotSpeed) * 0.5) - player->planeY * sin((player->rotSpeed) * 0.5);
        player->planeY = oldPlaneX * sin((player->rotSpeed) * 0.5) + player->planeY * cos((player->rotSpeed) * 0.5);
	}
	if(player->rL == 1)
	{
		double oldDirX = player->dirX;
        player->dirX = player->dirX * cos(-1*(player->rotSpeed) * 0.5) - player->dirY * sin(-1*(player->rotSpeed) * 0.5);
        player->dirY = oldDirX * sin(-1*(player->rotSpeed) * 0.5) + player->dirY * cos(-1*(player->rotSpeed) * 0.5);
        double oldPlaneX = player->planeX;
        player->planeX = player->planeX * cos(-1*(player->rotSpeed) * 0.5) - player->planeY * sin(-1*(player->rotSpeed) * 0.5);
        player->planeY = oldPlaneX * sin(-1*(player->rotSpeed) * 0.5) + player->planeY * cos(-1*(player->rotSpeed) * 0.5);
	}
	// printf("New posY = %f\nNew posX = %f\n", player->posY, player->posX);
	// put_square(*minimap, 1, (int)player->posX, (int)player->posY, 10);
	// mlx_put_image_to_window(minimap->mlx_ptr, minimap->win_ptr, minimap->ind, 0, 0);
	return(0);
}

int 	render_next_frame(all_data *everything)
{
	mlx_clear_window(everything->img->mlx_ptr, everything->img->win_ptr);
    // mlx_clear_window(everything->minimap->mlx_ptr, everything->minimap->win_ptr);
	// put_square(*everything->minimap, 2, (int)everything->player->posX, (int)everything->player->posY, 10);
	// mlx_put_image_to_window(everything->minimap->mlx_ptr, everything->minimap->win_ptr, everything->minimap->ind, 0, 0);
	movement(everything->player, everything->map, everything->minimap);
    drawFOV(everything, everything->map, everything->settings);
	setAndSort(everything, everything->listOfSprites, everything->settings);
	// put_square(*everything->minimap, 1, (int)everything->player->posX, (int)everything->player->posY, 10);
	// mlx_put_image_to_window(everything->minimap->mlx_ptr, everything->minimap->win_ptr, everything->minimap->ind, 0, 0);
	mlx_put_image_to_window(everything->img->mlx_ptr, everything->img->win_ptr, everything->img->ind, 0, 0);
	return (0);
}

int             key_hook_release(int keycode, player_data *player)
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

int             key_hook(int keycode, player_data *player)
{
	// put_square(*minimap, 2, (int)player->posX, (int)player->posY, 10);
	// mlx_put_image_to_window(minimap->mlx_ptr, minimap->win_ptr, minimap->ind, 0, 0);
	if (keycode == 124)
	{
		player->rR = 1;
    }
	if (keycode == 123)
    {
		player->rL = 1;
    }
    if (keycode == 13)
    {
		player->mF = 1;
    }
    if (keycode == 1)
    {
		player->mB = 1;
    }
	if (keycode == 0)
	{
		player->mL = 1;
	}
	if (keycode == 2)
	{
		player->mR = 1;
	}
	// printf("%i\n", keycode);
	return(0);
}

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int check_resolution_number(char *widthOrLength)
{
	int i;
	i = 0;
	while (i < ft_strlen((const char *)widthOrLength))
	{
		if(ft_isdigit(widthOrLength[i]) == 0)
		{
			printf("Error: bad resolution\n");
			return(1);
		}
		i++;
	}
	return(0);
}

int checkResNumber(char **res, int number, int length)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while(res[i][j])
		j++;
	if(j != length)
	{
		printf("Error\nBad argument\n");
		return(1);
	}
	while(res[i])
		i++;
	if(i != number)
	{
		printf("Error\nBad argument number\n");
		return(1);
	}
	return(0);
}

int setTex(const char *line, settings *settings, int l)
{
	char **res;

	res = ft_split(line, ' ');
	if(checkResNumber(res, 2, l) == 0)
	{
		if(res[0][0] == 'N' && res[0][1] == '0')
			settings->NO = res[1];
		if(res[0][0] == 'S' && res[0][1] == '0')
			settings->SO = res[1];
		if(res[0][0] == 'W' && res[0][1] == 'E')
			settings->WE = res[1];
		if(res[0][0] == 'E' && res[0][1] == 'A')
			settings->NO = res[1];
		if(res[0][0] == 'N' && res[0][1] == '0')
			settings->NO = res[1];
		if(res[0][0] == 'S' && res[0][1] == '\0')
			setting->S = res[1];
		return(0)
	}
	return(1);	
}

int set_resolution(const char *line, settings *settings)
{
	char **res;

	res = ft_split(line, ' ');
	if(res[0][1] != '\0' || res[0][0] != 'R')
	{
		printf("Error\nbad type indentifier\n");
		return(1);
	}
	if(check_resolution_number(res[1]) == 1)
		return(1);
	if(check_resolution_number(res[2]) == 1)
		return(1);
	settings->sW = ft_atoi(res[1]);
	settings->sH = ft_atoi(res[2]);
	return(0);
}

int line_correction(const char *line)
{
	size_t i;
	char *tmp;

	i = 0;
	tmp = (char *)line;
	if(!line)
		return(0);
	while(tmp[i] != '\0')
	{
		if(ft_isprint(tmp[i]) == 0 || tmp[i] == '"')
			tmp[i] = ' ';
		i++;
	}
	return(i);
}

int	check_line(const char *line, settings *settings)
{
	size_t line_length;
	int i;

	i = 0;
	line_length = line_correction(line);
	while(line[i])
	{
		if(line[i] == 'R')
		{
			if (set_resolution(line, settings) == 1)
				return(1);
			else
				return(2);
		}
		else if(line[i] == 'S' && line[i + 1] != 'O')
			setTex(line, setting, 1);
		else if(ft_strchr("NSWE", line[i]) != NULL)
		{
			setTex(line, setting, 2);
		}
	}
	return(0);
}

char **makeMap(t_list *head, int size)
{
    char **map = (char **)malloc(sizeof(char*) * (size + 1));
	int i;
	t_list *tmp;

	tmp = head;
	i = -1;
	while(tmp)
	{
		map[++i] = tmp->content;
		tmp = tmp->next;
	}
	i = -1;
	// while(map[++i])
	// 	ft_putendl_fd(map[i], 1);
	return(map);
}

void setDirPlane(char way, player_data *player)
{
	if(way == 'N')
	{
		player->dirX = 0;
		player->dirY = -1;
		player->planeX = 0.66;
		player->planeY = 0;
	}
	else if(way == 'S')
	{
		player->dirX = 0;
		player->dirY = 1;
		player->planeX = -0.66;
		player->planeY = 0;
	}
	else if(way == 'E')
	{
		player->dirX = 1;
		player->dirY = 0;
		player->planeX = 0;
		player->planeY = 0.66;
	}
	else if(way == 'W')
	{
		player->dirX = -1;
		player->dirY = 0;
		player->planeX = 0;
		player->planeY = -0.66;
	}
}

int main(int argc, char **argv)
{
	int fd;
	char **map;
	settings	settings;

    t_data img;
    t_data minimap;
    t_data minimapPlayer;
    
    player_data player;
    player.dirX = 0;
    player.dirY = 0;
    player.planeX = 0;
    player.planeY = 0;
    player.rotSpeed = 0.09;
    player.moveSpeed = 1;
	player.rR = 0;

	ray_data	raycasting;
	all_data	everything;
	tex_data	texture1;
	tex_data	sprite1;
	sprite_data	*listOfSprites;
	sprite_data *tmp;

	listOfSprites = NULL;

    everything.player = &player;
    everything.img = &img;
    everything.raycasting = &raycasting;
    // everything.minimap = &minimap;
    // everything.minimapPlayer = &minimapPlayer;
    everything.texture = &texture1;
	everything.sprite1 = &sprite1;
	everything.listOfSprites = listOfSprites;
	everything.numOfSprite = 0;
	everything.settings = &settings;

	if (argc != 2)
    {
		fd = open("map.cub", O_RDONLY);
		printf("argc != 2\n");
	}
	else
	{
		fd = open(argv[1], O_RDONLY);
		printf("argv[1] is used\n");
	}
	char *line = NULL;
	t_list *head = NULL;
	while (get_next_line(fd, &line))
	{
		if(check_line((const char *)line, everything.settings) == 0)
			ft_lstadd_back(&head, ft_lstnew(line));
		else if(check_line((const char *)line, everything.settings) == 1)
			return(0);
	}
	ft_lstadd_back(&head, ft_lstnew(line));
	everything.map = makeMap(head, ft_lstsize(head));
	printf("sW = %d\nsH = %d\n", everything.settings->sW, everything.settings->sH);
	raycasting.Zbuffer = (double *)malloc(sizeof(double) * everything.settings->sW);
	img.mlx_ptr = mlx_init();
    img.win_ptr = mlx_new_window(img.mlx_ptr, everything.settings->sW, everything.settings->sH, "Raycasting");
    
    // minimap.mlx_ptr = mlx_init();
    // minimap.win_ptr = mlx_new_window(minimap.mlx_ptr, everything.settings->sW, everything.settings->sH, "MiniMap");
    // minimap.x = 0;
    // minimap.y = 0;

    img.x = 0;
	img.y = 0;
	img.ind = mlx_new_image(img.mlx_ptr, everything.settings->sW, everything.settings->sH);
	img.addr = mlx_get_data_addr(img.ind, &img.bits_per_pixel, &img.line_length,
									&img.endian);

    texture1.relative_path = "gomer.png";
    texture1.ind = mlx_png_file_to_image(img.mlx_ptr, "gomer.png", &texture1.texWidth, &texture1.texHeight);
    texture1.addr = mlx_get_data_addr(texture1.ind, &texture1.bits_per_pixel, 
                                    &texture1.line_length, &texture1.endian);
	
	sprite1.relative_path = "barrel.png";
	sprite1.texHeight = 0;
	sprite1.texWidth = 0;
	sprite1.ind = mlx_png_file_to_image(img.mlx_ptr, "barrel.png", &sprite1.texWidth, &sprite1.texHeight);
	sprite1.addr = mlx_get_data_addr(sprite1.ind, &sprite1.bits_per_pixel, 
									&sprite1.line_length, &sprite1.endian);

    // minimap.ind = mlx_new_image(minimap.mlx_ptr, everything.settings->sW, everything.settings->sH);
    // minimap.addr = mlx_get_data_addr(minimap.ind, &minimap.bits_per_pixel, &minimap.line_length, &minimap.endian);

    // minimapPlayer.ind = mlx_new_image(minimap.mlx_ptr, 11, 11);
    // minimapPlayer.addr = mlx_get_data_addr(minimapPlayer.ind, &minimapPlayer.bits_per_pixel, &minimapPlayer.line_length, &minimapPlayer.endian);

	// listOfSprites = (sprite_data *)malloc(sizeof(sprite_data) * (5) + 1);
	int sprX;
	int sprY;
	int k = 0;

	sprX = 0;
	sprY = 0;

    for (int i = 0; i < 14; i++)
    {
        for (int j = 0; j < 33; j++)
        {
            if(ft_strchr("NSWE", everything.map[i][j]))
            {
                player.posX = j + 0.5;
                player.posY = i + 0.5;
				setDirPlane(everything.map[i][j], everything.player);
				everything.map[i][j] = '0';
				// put_square(minimap, 1, (int)player.posX, (int)player.posY, 10);
                // mlx_put_image_to_window(minimap.mlx_ptr, minimap.win_ptr, minimapPlayer.ind, j * 10, i * 10);
            }
			if(everything.map[i][j] == '2')
			{
				everything.numOfSprite++;
				tmp = everything.listOfSprites;
				// printf("numOfSprite = %d\n", everything.numOfSprite);
				everything.listOfSprites = (sprite_data *)malloc(sizeof(sprite_data) * (everything.numOfSprite));
				for(int l = 0; l < everything.numOfSprite - 1; l++)
				{
					everything.listOfSprites[l].x = tmp[l].x;
					everything.listOfSprites[l].y = tmp[l].y;
				}
				everything.listOfSprites[everything.numOfSprite - 1].x = j + 0.5;
				everything.listOfSprites[everything.numOfSprite - 1].y = i + 0.5;
				free(tmp);
				//k++;
			}
            // if(everything.map[i][j] == '1' || everything.map[i][j] == '2')
				// put_square(minimap, 0, j, i, 10);
                // mlx_put_image_to_window(minimap.mlx_ptr, minimap.win_ptr, minimap.ind, j * 10, i * 10);
        }
    }
	everything.spriteOrder = (int *)malloc(sizeof(int) * everything.numOfSprite);
	everything.spriteDist = (double *)malloc(sizeof(double) * everything.numOfSprite);
	// mlx_put_image_to_window(minimap.mlx_ptr, minimap.win_ptr, minimap.ind, 0, 0);
    // mlx_put_image_to_window(img.mlx_ptr, img.win_ptr, img.ind, 0, 0);
    mlx_hook(img.win_ptr, 2, 1L<<0, key_hook, everything.player);
	mlx_hook(img.win_ptr, 3, 1L<<0, key_hook_release, everything.player);
    mlx_loop_hook(img.mlx_ptr, render_next_frame, &everything);
    mlx_loop(img.mlx_ptr);
    // mlx_loop(minimap.mlx_ptr);
}
