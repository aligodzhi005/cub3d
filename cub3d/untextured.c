/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   untextured.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 11:16:20 by rvena             #+#    #+#             */
/*   Updated: 2021/04/17 22:25:44 by rvena            ###   ########.fr       */
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
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void create_screenshot2(int fd, all_data *everything)
{
	int32_t	x;
	int32_t	y;
	int		color;

	y = everything->settings->sH - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < everything->settings->sW)
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

void create_screenshot(all_data *everything)
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
	bitmap[0] = 'B';// просто символы  
	bitmap[1] = 'M';
	*((int *)(bitmap + 2)) = everything->settings->sH
	* everything->settings->sW * 4 + 54;// размер всего файла, 4 потому что цвет состоит из 4 параметров   
	*(int *)(bitmap + 10) = 54;
	*(int *)(bitmap + 14) = 40;
	*(int *)(bitmap + 18) = everything->settings->sW;//ширина скриншота
	*(int *)(bitmap + 22) = everything->settings->sH;//высота скриншота
	*(bitmap + 26) = 1;
	*(bitmap + 28) = 32;//количество бит на пиксель
	write(fd, bitmap, 54);
	create_screenshot2(fd, everything);
}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//oooooooooooooooooooooooooooooooooooooooooooooooooooooo
int	read_file(all_data *everything, int *fd)
{
	int res_check_line;
	char *line;
	t_list *head;
	t_list *tmp;

	line = NULL;
	head = NULL;
	while (get_next_line(*fd, &line))
	{
		res_check_line = check_line((const char *)line, everything->settings);
		if(res_check_line == 0)
			ft_lstadd_back(&head, ft_lstnew(line));
		else if(res_check_line == 1)
			return(1);
		else 
			free(line);
	}
	ft_lstadd_back(&head, ft_lstnew(line));
	everything->map = makeMap(head, ft_lstsize(head), everything->settings);
	while(head)
	{
		tmp = head;
		head = head->next;
		free(tmp);
		free(tmp->content);
	}
	return(0);
}
//oooooooooooooooooooooooooooooooooooooooooooooooooooooo

//######################################################
int check_argv_cub(char *argv, int *fd)
{
	char *tmp;
	int ret;

	tmp = ft_strnstr(argv, ".cub", ft_strlen(argv));
	if(tmp != 0 && *(tmp + 4) == '\0')
	{
		*fd = open(argv, O_RDONLY);
		ret = read(*fd, tmp, 0);
		if(ret == -1)
		{
			printf("Error\n%s is not file\n", argv);
			close(*fd);
			exit(-1);
		}
		return(0);
	}
	printf("Error\nBad map file");
	return(1);
}

int check_read_argv(int argc,char **argv, int*fd, int *screen)
{
	if(argc == 1)
	{
		*fd = open("map.cub", O_RDONLY);
		*screen = 0;
		return(0);
	}
	printf("Блять\n");
	if (argc == 2)
		return(check_argv_cub(argv[1], fd));
	else if (argc == 3)
	{
		if(ft_strncmp(argv[2], "--save", ft_strlen(argv[1])) == 0)
			if(check_argv_cub(argv[1], fd) == 0)
			{
				*screen = 1;
				return(0);
			}
		printf("Error\nBad argument after or before ./cub3d\n");
		exit(-1);
	}
	printf("Error\nToo many arguments after ./cub3d or there is no arguments");
	return(1);
}
//######################################################

////////////////////////////////////////////////////////////
static void setPlayer(all_data *everything, int i, int j)
{
	if(everything->player->posX == 0)
	{
		everything->player->posX = j + 0.5;
		everything->player->posY = i + 0.5;
		setDirPlane(everything->map[i][j], everything->player);
		everything->map[i][j] = '0';
		// printf("%c", everything.map[i][j]);
	}
	else
	{
		printf("Error\nToo many players\n");
		exit(-1);
	}
}

static void mallocListOfSprites(all_data *everything, sprite_data *tmp)
{
	everything->listOfSprites = (sprite_data *)malloc(sizeof(sprite_data) * (everything->numOfSprite));
	if(everything->listOfSprites == NULL)
	{
		printf("Error\nMalloc listOfSprites error\n");
		free(tmp);
		exit(-1);
	}
}

static void setListOfSprite(all_data *everything, int i, int j)
{
	sprite_data *tmp;
	int l;

	l = 0;
	// everything->listOfSprites = NULL;
	everything->numOfSprite++;
	tmp = everything->listOfSprites;
	mallocListOfSprites(everything, tmp);
	while(l < everything->numOfSprite - 1)
	{
		everything->listOfSprites[l].x = tmp[l].x;
		everything->listOfSprites[l].y = tmp[l].y;
		l++;
	}
	everything->listOfSprites[everything->numOfSprite - 1].x = j + 0.5;
	everything->listOfSprites[everything->numOfSprite - 1].y = i + 0.5;
	free(tmp);
}

int findPlayerSprite(all_data *everything)
{
	int i;
	int j;

	i = 0;
	while(i < everything->settings->mapH)
	{
		j = 0;
		while(j < everything->settings->mapW)
		{
			if(ft_strchr("NSWE", everything->map[i][j]))
				setPlayer(everything, i, j);
			else if(everything->map[i][j] == '2')
				setListOfSprite(everything, i, j);
			j++;
		}
		i++;
	}
	if(everything->player->posX == 0)
	{
		printf("Error\nNo player\n");
		exit(-1);
	}
	everything->spriteOrder = (int *)malloc(sizeof(int) * everything->numOfSprite);
	everything->spriteDist = (double *)malloc(sizeof(double) * everything->numOfSprite);
	return(0);
}
////////////////////////////////////////////////////

int main(int argc, char **argv)
{
	// sleep(15);
	int fd;
	// int res_check_line;
	// char **map;
	
	// res_check÷_line = 0;

	ray_data	raycasting;
	all_data	everything;

	// sprite_data *tmp;
	everything.listOfSprites = NULL;
	everything.raycasting = &raycasting;
	everything.numOfSprite = 0;
	everything.settings = init_settings();
	everything.screenshot = 0;
	everything.player = init_player();
	// printf("Blyat\n");
	if(check_read_argv(argc, argv, &fd, &everything.screenshot))
		exit(1);
	// printf("screen = %d\n", everything.screenshot);
	if(read_file(&everything, &fd) == 1)
		exit(1);
	// printf("Жопа\n");
	if (checkMap(everything.map, everything.settings))
		exit(0);
	if(findPlayerSprite(&everything))
		exit(1);
	raycasting.Zbuffer = (double *)malloc(sizeof(double) * everything.settings->sW);
	everything.img = initImgStr(everything.settings);
	// img.mlx_ptr = mlx_init();
    // img.win_ptr = mlx_new_window(img.mlx_ptr, everything.settings->sW, everything.settings->sH, "Raycasting");
	mlx_get_screen_size(everything.img->mlx_ptr, &everything.settings->pcscrW, &everything.settings->pcscrH);
	if(everything.settings->sW > everything.settings->pcscrW)
		everything.settings->sW = everything.settings->pcscrW;
	if(everything.settings->sH > everything.settings->pcscrH)
		everything.settings->sH = everything.settings->pcscrH;
	init_text(&everything);
	// img.ind = mlx_new_image(img.mlx_ptr, everything.settings->sW, everything.settings->sH);
	// img.addr = mlx_get_data_addr(img.ind, &img.bits_per_pixel, &img.line_length,
	// 								&img.endian);
    // texture1.ind = mlx_png_file_to_image(img.mlx_ptr, "/Users/rvena/Desktop/cub3d/marge.png", &texture1.texWidth, &texture1.texHeight);
	// if(texture1.ind == 0)
	// {
	// 	printf("Error\nBad photo for texture\nTry another phoro\n");
	// 	exit(-1);
	// }
	// texture1.addr = mlx_get_data_addr(texture1.ind, &texture1.bits_per_pixel, 
    //                                 &texture1.line_length, &texture1.endian);
	// sprite1.texHeight = 0;
	// sprite1.texWidth = 0;
	everything.sprite1 = initSpr(&everything);
	// sprite1.ind = mlx_png_file_to_image(everything.img->mlx_ptr, everything.settings->S, &sprite1.texWidth, &sprite1.texHeight);
	// sprite1.addr = mlx_get_data_addr(sprite1.ind, &sprite1.bits_per_pixel, 
	// 								&sprite1.line_length, &sprite1.endian);
	// everything.spriteOrder = (int *)malloc(sizeof(int) * everything.numOfSprite);
	// everything.spriteDist = (double *)malloc(sizeof(double) * everything.numOfSprite);
	mlx_hook(everything.img->win_ptr, 17, 0, finish_game, &everything);
	mlx_hook(everything.img->win_ptr, 2, 1L<<0, key_hook, everything.player);
	mlx_hook(everything.img->win_ptr, 3, 1L<<0, key_hook_release, everything.player);
	if(everything.screenshot == 1)
	{
		render_next_frame(&everything);
		return(1);
	}
	mlx_loop_hook(everything.img->mlx_ptr, render_next_frame, &everything);
	mlx_loop(everything.img->mlx_ptr);
}
