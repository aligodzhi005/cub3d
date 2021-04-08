/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   untextured.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 11:16:20 by rvena             #+#    #+#             */
/*   Updated: 2021/04/08 20:22:08 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int checkWhtSpc(char chr)
{
	if(chr != ' ' && chr != '\t' 
		&& chr != '\n' && chr != '\v'
		&& chr != '\f' && chr != '\r')
		return(0);
	return (1);
}

int lineEmptyOrNot(char *line)
{
	int i = 0;
	while (line[i] != '\0')
	{
		if(checkWhtSpc(line[i]) == 0)
			return(0);
		i++;
	}
	return(1);
}

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
	mlx_do_sync(everything->img->mlx_ptr);
	// mlx_loop(everything->img->mlx_ptr);
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
		if(ft_isdigit(widthOrLength[i]) == 0 || i >= 5)
		{
			printf("Error:\nBad resolution\n");
			return(1);
		}
		i++;
	}
	return(0);
}

int printRepeatErr(void)
{
	printf("Error\nRepeatable type indentifier\n");
	return(1);
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
		printf("Error\nBad number of arguments\n");
		return(1);
	}
	return(0);
}

int setTexPath(const char *line, settings *settings, int d)
{
	char *tmp;

	tmp = (char *)line;
	while(checkWhtSpc(*tmp) == 1)
		tmp++;
	if(d == 1)
		settings->NO = tmp;
	else if(d == 2)
		settings->SO = tmp;
	else if(d == 3)
		settings->WE = tmp;
	else if(d == 4)
		settings->EA = tmp;
	else if(d == 5)
		settings->S = tmp;
	return(0);
}

// int checkTexPath2(const char *line, settings *settings)
// {
// 	if(res[0][0] == 'E' && res[0][1] == 'A')
// 		if(settings->EA == NULL)
// 		// {
// 		// 	settings->EA = res[1];
// 		// 	return(0);
// 		// }
// 		return(setTexPath())
// 		else
// 			return(printRepeatErr());
// 	else if(res[0][0] == 'S' && res[0][1] == '\0')
// 		{
// 			if(settings->S == NULL)
// 			{
// 				settings->S = res[1];
// 				return(0);
// 			}
// 			else
// 			{
// 				return(printRepeatErr());
// 			}
// 		}
// 	printf("Error\nBad argument\n");
// 	return(1);
// }

// int checkTexPath(const char *line, settings *settings)
// {
// 	if(res[0][0] == 'N' && res[0][1] == 'O')
// 		if(settings->NO == NULL)
// 		{
// 			settings->NO = res[1];
// 			return(0);
// 		}
// 		else
// 			return(printRepeatErr());
// 	else if(res[0][0] == 'S' && res[0][1] == 'O')
// 		if(settings->SO == NULL)
// 		{
// 			settings->SO = res[1];
// 			return(0);
// 		}
// 		else
// 			return(printRepeatErr());
// 	else if(res[0][0] == 'W' && res[0][1] == 'E')
// 		{
// 			if(settings->WE == NULL)
// 			{
// 				settings->WE = res[1];
// 				return(0);
// 			}
// 			else
// 			{
// 				return(printRepeatErr());
// 			}
// 		}
// 	return(checkTexPath2(res, settings));
// }

int setTex(const char *line, settings *settings, int l)
{
	int i;

	i = 0;
	// res = ft_split(line, ' ');
	// if(checkResNumber(res, 2, l) == 0)
	// {
		if(line[i] == 'N' && line[i + 1] == 'O')
			if(settings->NO == NULL)
				return(setTexPath(&line[i + 2], settings, 1));
			else
				return(printRepeatErr());
		else if(line[i] == 'S' && line[i + 1] == 'O')
			if(settings->SO == NULL)
				return(setTexPath(&line[i + 2], settings, 2));
			else
				return(printRepeatErr());
		else if(line[i] == 'W' && line[i + 1] == 'E')
			if(settings->WE == NULL)
				return(setTexPath(&line[i + 2], settings, 3));
			else
				return(printRepeatErr());
		else if(line[i] == 'E' && line[i + 1] == 'A')
			if(settings->EA == NULL)
				return(setTexPath(&line[i + 2], settings, 4));
			else
				return(printRepeatErr());
		else if(line[i] == 'S' && checkWhtSpc(line[i + 1]) == 1)
			{
			if(settings->S == NULL)
				return(setTexPath(&line[i + 2], settings, 5));
			else
				return(printRepeatErr());
			}
		// printf("Error\nBad type argument\n");
		// return(1);
		// return(checkTexPath(line, settings));
	//} 
	return(1);	
}

int line_correction(const char *line)
{
	size_t i;
	int isSpace;
	char *tmp;

	i = 0;
	tmp = (char *)line;
	if(!line)
		return(0);
	while(tmp[i] != '\0')
	{
		// if(ft_isprint(tmp[i]) == 0 || tmp[i] == '"')
		if(checkWhtSpc(tmp[i]) == 1)
			tmp[i] = ' ';
		i++;
	}
	return(i);
}

char	**ft_free_res(char **res)
{
	int k;

	k = 0;
	while (res[k] != NULL)
	{
		free(res[k]);
		k++;
	}
	free(res);
	return (NULL);
}

int set_resolution(const char *line, settings *settings)
{
	char **res;
	
	line_correction(line);
	if(settings->sW != 0 && settings->sH != 0)
		return(printRepeatErr());
	res = ft_split(line, ' ');
	if(res[0][1] != '\0' || res[0][0] != 'R')
	{
		printf("Error\nBad argument\n");
		return(1);
	}
	if(check_resolution_number(res[1]) == 1 || 
		checkResNumber(res, 3, 1) == 1)
		return(1);
	if(check_resolution_number(res[2]) == 1)
		return(1);
	settings->sW = ft_atoi(res[1]);
	settings->sH = ft_atoi(res[2]);
	ft_free_res(res);
	// free(line);
	return(0);
}

int checkSettings(settings *settings, const char *line)
{
	int i;

	i = 0;
	if(settings->sW != 0 && settings->sH != 0
		&& settings->floor != -1 && settings->ceilling != -1)	
		if(settings->NO != NULL && settings->SO != NULL	&& 
			settings->WE != NULL && settings->EA != NULL
			&& settings->S != NULL)
			{
				// if(line[i] == '\0')
				// 	return(1);
				while(line[i] != '\0')
				{
					if(ft_isprint(line[i++]))
						return (1);
					// i++;
				}
			}
	if(lineEmptyOrNot((char *)line) == 1)
		return(1);
	return(0);
}

int printBadArg(void)
{
	printf("Error\nBad Argument\n");
	return(1);
}

int countNumberOfDigit(int i)
{
	int count;

	count = 0;
	if (i == 0)
		return (1);
	while(i != 0)
	{
		i /= 10;
		count++;
	}
	return(count);
}

int setColor(const char *line, long *color)
{
	char	*tmp;
	int		num;
	int		i;

	num = 16777216;
	tmp = (char *)line;
	while(*tmp)
	{
		while(checkWhtSpc(*tmp) == 1)
			tmp++;
		num /= 256;
		i = ft_atoi(tmp);
		if(*color == -1)
			*color += 1;
		*color += i * num;
		tmp += countNumberOfDigit(i);
		if(*color < 0 || num < 1 || i > 255)
		{
			printf("Error\nBad color\n");
			return(1);
		}
		while(checkWhtSpc(*tmp) == 1 || *tmp == ',')
			tmp++;
	}
	// free(line);
	return(0);
}

int setColFC(const char *line, settings *settings)
{
	int i;

	i = 0;
	if (line[i] == 'F' && checkWhtSpc(line[i + 1]) == 1)
		return(setColor(&line[i + 1], &settings->floor));
	else if (line[i] == 'C' && checkWhtSpc(line[i + 1]) == 1)
		return(setColor(&line[i + 1], &settings->ceilling));
	else 
		return(printBadArg());
	// if(checkWhtSpc(line[i++]) == 0)
	// 	return(printBadMap());
	// while(checkWhtSpc(line[i]))
	// 	i++; 
	// if(ft_isdigit(line[i]) == 1)
}

int	check_line(const char *line, settings *settings)
{
	size_t line_length;
	int i;

	i = 0;
	line_length = checkSettings(settings, line);
	if(line_length == 1)
		return(0);
	// else if(line_length == 2)
	// 	return(2);
	// line_length = line_correction(line);
	// if(line_length > settings->mapW)
	// 	settings->mapW = line_length;
	while(line[i])
	{
		if(ft_strchr("RNSWEFC", line[i]) == NULL)
			if(checkWhtSpc(*line) == 0)
			{
				printf("Error\nBad argument\n");
				return(1);	
			}
		if(line[i] == 'R')
		// if(ft_strnstr(line, "R", line_length))
		{
			if (set_resolution(line, settings) == 1)
				return(1);
			else
				return(2);
		}
		else if(ft_strchr("FC", line[i]) != NULL)
		// else if(ft_strnstr(line, "S ", line_length))
		{
			if(setColFC(&line[i], settings) != 0)
				return(1);
			else
				return(2);
		}
		else if(ft_strchr("NSWE", line[i]) != NULL)
		// else if(ft_strchr("NSWE", line[i]) != NULL && ft_strchr("OAE", line[i + 1]) != NULL)
		{
			if(setTex(&line[i], settings, 2) == 0)
				return(2);
			else
				return(1);
		}
		i++;
	}
	printf("Error\nBad argument\n");
	return(1);
}

char **makeMap(t_list *head, int size, settings *settings)
{
	char *vis;
	int i;
	t_list *tmp;
	char **map;

	tmp = head;
	vis = tmp->content;
	i = 0;
	while(lineEmptyOrNot(vis))
	{
		i++;
		tmp = tmp->next;
		vis = tmp->content;
	}
	settings->mapH = size - i;
	map = (char **)malloc(sizeof(char*) * (size - i));
	i = -1;
	while(tmp)
	{
		vis = tmp->content;
		if(lineEmptyOrNot(vis) == 0)
			map[++i] = vis;
		else
		{
			printf("Error\nBad map");
			free(map);
			return(NULL);
		}
		tmp = tmp->next;
	}
	i = -1;
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

int printBadMap(void)
{
	printf("Error\nBad map\n");
	return(1);
}

int mapNormalize(char **map, settings *settings)
{
	char *tmp;
	// char *spc;
	size_t line_length;
	int i;

	// line_length = 0;
	while(i < settings->mapH)
	{
		line_length = ft_strlen(map[i]);
		if(line_length < settings->mapW)
		{
			tmp = map[i];
			map[i] = (char *)malloc((settings->mapW + 1) * sizeof(char));
			map[i][settings->mapW + 1] = '\0';
			map[i] = ft_memcpy(map[i], tmp, line_length);
			while(line_length < settings->mapW + 1)
			// {
				map[i][line_length++] = ' ';
				// line_length++;
			// }
			free(tmp);
		}
		i++;
	}
	return(0);
}

int checkMap(char **map, settings *settings)
{
	int i;
	int j; 
	int start;

	start = 0;
	i = 0;
	// моя задумка в том, чтобы проверять есть ли символ в списке разрешенных - это во-первых
	// должен подниматься флаг startHor, если наткнулись на 1 - это во-вторых
	// если символ является 0,N,S,W,E,2, то должен быть поднят флаг startHor и после него не должно быть ' ' или '\0' - это в-третьих
	// такая же проверка для вертикальной линии
	// check horizontal line


	while(i < settings->mapH)
	{
		j = 0;
		while(map[i][j] != '\0')
		{
			if(ft_strchr("012NSWE ", map[i][j]) == NULL)
				return(printBadMap());
			else if(map[i][j] == '1')
				start = 1;
			else if(ft_strchr("02NSWE", map[i][j]) != NULL)
				if(start != 1 || map[i][j + 1] == ' ' || map[i][j + 1] == '\0' || map[i][j - 1] == ' ')
					return(printBadMap());
			j++;
		}
		if(j > settings->mapW)
			settings->mapW = j;
		i++;
	}
	printf("%d\n", settings->mapW);
	mapNormalize(map, settings);
	j = 0;
	while(j < settings->mapW)
	{
		i = 0;
		while(i < settings->mapH)
		{
			if(map[i][j] == '1')
				start = 1;
			else if(ft_strchr("02NSWE", map[i][j]) != NULL)
				if(start != 1 || map[i + 1][j] == ' ' || map[i + 1][j] == '\0' || map[i - 1][j] == ' ')
					return(printBadMap());
			i++;
		}
		j++;
	}
	return(0);
}

int main(int argc, char **argv)
{
	int fd;
	int res_check_line;
	char **map;
	settings	settings;
	settings.sW = 0;
	settings.sH = 0;
	settings.NO = NULL;
	settings.SO = NULL;
	settings.WE = NULL;
	settings.EA = NULL;
	settings.S = NULL;
	settings.floor = -1;
	settings.ceilling = -1;
	settings.mapH = 0;
	settings.mapW = 0;

	res_check_line = 0;
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
		res_check_line = check_line((const char *)line, everything.settings);
		if(res_check_line == 0)
			ft_lstadd_back(&head, ft_lstnew(line));
		else if(res_check_line == 1)
			return(0);
	}
	ft_lstadd_back(&head, ft_lstnew(line));
	printf("S = %s\nNO = %s\n", everything.settings->S, everything.settings->NO);
	// printf("%s\n", everything.map[0]);
	everything.map = makeMap(head, ft_lstsize(head), &settings);
	if(everything.map == NULL)
		return(0);
		printf("%s\n", everything.map[0]);
	printf("sW = %d\nsH = %d\n", everything.settings->sW, everything.settings->sH);
	printf("mapH = %d\n", everything.settings->mapH);
	if (checkMap(everything.map, everything.settings))
		return(0);
	raycasting.Zbuffer = (double *)malloc(sizeof(double) * everything.settings->sW);
	// printf("%s\n", img.mlx_ptr);
	img.mlx_ptr = mlx_init();
	printf("%s\n", img.mlx_ptr);
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
    texture1.ind = mlx_png_file_to_image(img.mlx_ptr, everything.settings->NO, &texture1.texWidth, &texture1.texHeight);
    texture1.addr = mlx_get_data_addr(texture1.ind, &texture1.bits_per_pixel, 
                                    &texture1.line_length, &texture1.endian);
	
	// sprite1.relative_path = "barrel.png";
	sprite1.texHeight = 0;
	sprite1.texWidth = 0;
	sprite1.ind = mlx_png_file_to_image(img.mlx_ptr, everything.settings->S, &sprite1.texWidth, &sprite1.texHeight);
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

    for (int i = 0; i < everything.settings->mapH; i++)
    {
        for (int j = 0; j < everything.settings->mapW; j++)
        {
			// printf("%c", (everything.map)[i][j]);
            if(ft_strchr("NSWE", everything.map[i][j]))
            {
                player.posX = j + 0.5;
                player.posY = i + 0.5;
				setDirPlane(everything.map[i][j], everything.player);
				everything.map[i][j] = '0';
				printf("%c", everything.map[i][j]);
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
				printf("%c", everything.map[i][j]);
				//k++;
			}
			if(everything.map[i][j] == ' ')
				printf("A");
            // if(everything.map[i][j] == '1' || everything.map[i][j] == '2')
				// put_square(minimap, 0, j, i, 10);
                // mlx_put_image_to_window(minimap.mlx_ptr, minimap.win_ptr, minimap.ind, j * 10, i * 10);
        }
		printf("\n");
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
