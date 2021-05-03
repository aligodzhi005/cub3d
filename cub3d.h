/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <rvena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:37:47 by rvena             #+#    #+#             */
/*   Updated: 2021/04/25 03:33:16 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include "./minilibx_mms_20200219/mlx.h"
# include "./libft/libft.h"
# include "get_next_line.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_spr_data
{
	double	x;
	double	y;
}				t_sprite_data;

typedef struct s_pl_data
{
	double	posX;
	double	posY;
	double	planeX;
	double	planeY;
	double	dirX;
	double	dirY;
	float	rotSpeed;
	double	moveSpeed;
	int		mF;
	int		mL;
	int		mR;
	int		mB;
	int		rR;
	int		rL;
}				t_plr_data;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*ind;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			x;
	int			y;
}				t_data;

typedef struct s_te_data
{
	void		*ind;
	char		*relative_path;
	int			texWidth;
	int			texHeight;
	char		*addr;
	int			line_length;
	int			bits_per_pixel;
	int			endian;
	int			drawStart;
	int			drawEnd;
	double		spriteX;
	double		spriteY;
	int			sprScrX;
	int			sprH;
	int			drawStartY;
	int			drawEndY;
	int			sprW;
	int			drawStartX;
	int			drawEndX;
	int			texX;
}				t_tex_data;

typedef struct s_ray_data
{
	double		rayDirX;
	double		rayDirY;
	double		cameraX;
	double		cameraY;
	int			mapX;
	int			mapY;
	double		sideDistX;
	double		sideDistY;
	double		deltaDistX;
	double		deltaDistY;
	int			stepX;
	int			stepY;
	int			hit;
	double		perpWallDist;
	int			side;
	double		*Zbuffer;
	double		wallX;
}				t_ray_data;

typedef struct s_set_data
{
	int			sW;
	int			sH;
	char		*NO;
	char		*SO;
	char		*WE;
	char		*EA;
	char		*S;
	char		**path_mas;
	long		floor;
	long		ceilling;
	int			mapW;
	int			mapH;
	int			pcscrW;
	int			pcscrH;
}				t_settings;

typedef struct s_a_data
{
	t_plr_data		*player;
	t_data			*img;
	t_ray_data		*raycasting;
	t_data			*minimap;
	t_data			*minimapPlayer;
	t_tex_data		*texture;
	t_tex_data		*texture1;
	t_tex_data		*texture2;
	t_tex_data		*texture3;
	t_tex_data		*texture4;
	t_tex_data		*tex_mas;
	t_tex_data		*sprite1;
	t_sprite_data	*sprite;
	int				numOfSprite;
	int				*spriteOrder;
	double			*spriteDist;
	t_sprite_data	*listOfSprites;
	t_settings		*t_settings;
	char			**map;
	int				screenshot;
}					t_all_data;

void		setBasRayPar(t_ray_data *ray, t_all_data *ever, int x, char **map);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		drawFOV(t_all_data *everything, char **map, t_settings *t_settings);
void		setAndSort(t_all_data *ever,
				t_sprite_data *listOfSprites, t_settings *t_settings);
int			get_next_line(int fd, char **line);
int			checkWhtSpc(char chr);
int			lineEmptyOrNot(char *line);
int			movement(t_plr_data *player, char **map);
int			render_next_frame(t_all_data *everything);
int			key_hook_release(int keycode, t_plr_data *player);
int			key_hook(int keycode, t_plr_data *player);
int			check_line(const char *line, t_settings *t_settings);
int			checkMap(char **map, t_settings *t_settings);
int			checkResNumber(char **res, int number, int length);
int			check_read_argv(int argc, char **argv, int*fd, int *screen);
int			check_resolution_number(char *widthOrLength,
				t_settings *t_settings, int j);
int			setTex(const char *line, t_settings *t_settings);
char		**makeMap(t_list *head, int size, t_settings *t_settings);
int			chooseFlOrCl(const char *line, t_settings *t_settings);
int			setColor(const char *line, long *color);
int			printBadArg(void);
int			printBadMap(void);
int			printRepeatErr(void);
void		printfMallocMap(void);
void		printfMallocTexPath(void);
void		printfRepeatableColor(void);
void		setDirPlane(char way, t_plr_data *player);
t_settings	*init_t_settings(void);
t_plr_data	*init_player(void);
void		create_screenshot(t_all_data *everything);
void		init_text(t_all_data	*everything);
void		init_path_mas(t_settings *t_settings);
int			finish_game(t_all_data *everything);
t_data		*initImgStr(t_settings	*t_settings);
t_tex_data	*initSpr(t_all_data	*everything);
void		initEverything1(t_all_data *everything);
void		initEverything2(t_all_data *everything);
void		setAndDraw(t_all_data *ever,
				t_sprite_data *listOfSprites, int i, t_settings *t_settings);
int			set_resolution(const char *line, t_settings *t_settings);
void		drawFloorCeil(t_tex_data *temp,
				t_all_data *everything, int x, int y);
int			setTexX(t_all_data *everything, t_tex_data *temp);
double		setParForSpr(t_all_data *ever, t_sprite_data *listOfSprites,
				int i, t_tex_data *spr);
void		drawSprite(t_all_data *ever, t_tex_data	*spr,
				t_settings *set, double trFY);
void		rotation(t_plr_data *player, int i);
int			setTexPath(const char *line, char **p);
void		create_screenshot(t_all_data *everything);
void		setListOfSprite(t_all_data *everything, int i, int j);
int			findPlayerSprite(t_all_data *everything);
void		setPlayer(t_all_data *everything, int i, int j);
void		countComma(char *tmp);

#endif