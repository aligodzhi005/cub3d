/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 20:33:00 by rvena             #+#    #+#             */
/*   Updated: 2021/02/20 20:33:02 by rvena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minilibx_mms_20200219/mlx.h"

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	void        *ind;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
	int			x;
	int			y;
}				t_data;

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void			put_square(t_data *img, int col)
{
    int x;
    int y;

    x = 0;
    y = 0;
    
    while(y < 300)
    {
        x = 0;
        while(x < 300)
        {
            if(col == 0)
                my_mlx_pixel_put(img, x, y, 0xFFFFFF);
            else 
                my_mlx_pixel_put(img, x, y, 0x0000FF00);
            x++;
        }
        y++;
    }
}



int 	render_next_frame(t_data *img)
{
		mlx_clear_window(img->mlx_ptr, img->win_ptr);
		mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->ind, img->x, img->y);
		return (0);
}

void			create_img(t_data *img)
{
	img->x = 0;
	img->y = 0;
	img->ind = mlx_new_image(img->mlx_ptr, 301, 151);
	img->addr = mlx_get_data_addr(img->ind, &img->bits_per_pixel, &img->line_length,
									&img->endian);
}
void			put_triangle(t_data *img)
{
	int		x;
	int		y;
	int		z;
	int		k;

	k = 1;
	x = 0;

	while(x < 300)
	{
		y = 150;
		z = 0;
		while(z < k)
		{
			my_mlx_pixel_put(img, x, y, 0x00FF0000);
			y--;
			z++;
		}
		x++;
		if(x < 150)
			k++;
		else
			k--; 
	}
}

int             key_hook(int keycode, t_data *vars)
{
	if (keycode == 2)
	{
		// mlx_destroy_image(vars->mlx_ptr, vars->ind);
		// create_img(vars);
		put_square(vars, 0);
	}
	// if (keycode == 0 && vars->x > 0)
	// 	vars->x -= 20;
	// if (keycode == 1 && vars->y < 930)
	// 	vars->y += 20;
	// if (keycode == 13 && vars->y > 0)
	// 	vars->y -= 20;

	printf("%i\n", keycode);
    printf("Hello from key_hook!\n");
	return(0);
}





int main(void)
{
	t_data	img_gomer;
	t_data	img;
	int		width;
	int		height;

	char		*path = "gomer.png";
	
	img.mlx_ptr = mlx_init();
	img.win_ptr = mlx_new_window(img.mlx_ptr, 1920, 1080, "test");
	
	img_gomer.mlx_ptr = img.mlx_ptr;
	img_gomer.win_ptr = img.win_ptr;
	img_gomer.ind = mlx_png_file_to_image(img.mlx_ptr, path, &width, &height);

	create_img(&img);
	
	put_triangle(&img);

	mlx_key_hook(img.win_ptr, key_hook, &img);

	mlx_put_image_to_window(img.mlx_ptr, img.win_ptr, img.ind, img.x, img.y);
	mlx_put_image_to_window(img_gomer.mlx_ptr, img_gomer.win_ptr, img_gomer.ind, 500, 500);
	mlx_loop_hook(img.mlx_ptr, render_next_frame, &img);
	mlx_loop(img.mlx_ptr);
}
