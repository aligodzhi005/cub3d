#include <stdio.h>
#include "minilibx_mms_20200219/mlx.h"

int main(void)
{
    void    *mlx;
    void    *win;
    void    *img;
    char    *relative_path = "gomer.png";
    int     img_width;
    int     img_height;

    mlx = mlx_init();
    win = mlx_new_window(mlx, 1920, 1080, "Gomer");
            //mlx_png_file_to_image(void *mlx_ptr, char *file, int *width, int *height);
    img = mlx_png_file_to_image(mlx, relative_path, &img_width, &img_height);
    mlx_put_image_to_window(mlx, win, img, 500, 500);
    printf("height = %d\nwidth = %d\n", img_height, img_width);
    mlx_put_image_to_window(mlx, win, img, 100, 100);
    mlx_loop(mlx);
}