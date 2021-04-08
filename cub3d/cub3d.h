/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:37:47 by rvena             #+#    #+#             */
/*   Updated: 2021/04/08 18:40:22 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_3D_H
# define CUB_3D_H

#define mapWidth 33
#define mapHeight 14
// #define screenWidth 640
// #define screenHeight 480

#include <math.h>
#include "./minilibx_mms_20200219/mlx.h"
#include "./libft/libft.h"
#include "get_next_line.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct spr_data
{
    float	x;
    float	y;
}               sprite_data;

typedef struct p_data
{
    double posX;
    double posY;
    double planeX;
    double planeY;
    double dirX;
    double dirY;
    float rotSpeed;
    double moveSpeed;
	int		mF;
	int		mL;
	int		mR;
	int		mB;
	int		rR;
	int		rL;
}              player_data;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*ind;
	char		*addr;
	int			bits_per_pixel;
	int         line_length;
	int         endian;
	int         x;
	int         y;
}				t_data;

typedef struct te_data
{
	void        *ind;
    char        *relative_path;
    int         texWidth;
    int         texHeight;
    char        *addr;
    int         line_length;
    int         bits_per_pixel;
    int         endian;
}               tex_data;

typedef struct r_data
{
    double	rayDirX;
    double	rayDirY;
    double	cameraX;
    double	cameraY;
    int		mapX;
    int		mapY;
    double	sideDistX;
    double	sideDistY;
    double	deltaDistX;
    double	deltaDistY;
    int		stepX;
    int		stepY;
    int		hit;
    double	perpWallDist;
    int		side;
	double	*Zbuffer;
    double	wallX;//where exactly the wall was hit
}				ray_data;

typedef struct set_data
{
	int		sW;
	int		sH;
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	char	*S;
	long	floor;
	long	ceilling;
	int		mapW;
	int		mapH;
}				settings;

typedef struct a_data
{
    player_data		*player;
    t_data			*img;
    ray_data		*raycasting;
    t_data			*minimap;
    t_data			*minimapPlayer;
    tex_data		*texture;
	tex_data		*sprite1;
    sprite_data		*sprite;
	int				numOfSprite;
	int				*spriteOrder;
	double			*spriteDist;
	sprite_data		*listOfSprites;
	settings		*settings;
	char			**map;
}				all_data;

//void	setBasRayPar3(ray_data *raycasting, player_data *player, int worldMap[24][24]);
//void	setBasRayPar2(ray_data *raycasting, player_data *player, int worldMap[24][24]);
void    setBasRayPar(ray_data *raycasting, player_data *player, int x, char **map, settings *settings);
//void	drawVertLine(ray_data *raycasting, t_data *img, int x);
void    my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	drawFOV(all_data *everything, char **map, settings *settings);
void	setAndSort(all_data *ever, sprite_data *listOfSprites, settings *settings);
int		get_next_line(int fd, char **line);
int 	line_correction(const char *line);

#endif