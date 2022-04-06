NAME = cub3D
SRCS = setBasRayPar.c \
	   untextured.c \
	   get_next_line.c \
	   drawSprite.c \
	   drawFOVUtils.c \
	   drawFOV.c \
	   srcs/print_errors/print_errors.c \
	   srcs/generalFunctions.c \
	   srcs/mlxFunctions.c \
	   srcs/movement.c \
	   srcs/chooseFlOrCl.c \
	   srcs/create_screenshot.c \
	   srcs/findPlayerSprite.c \
	   srcs/checkers/check_line.c \
	   srcs/checkers/check_map.c \
	   srcs/checkers/check_res_number.c \
	   srcs/checkers/check_resolution_number.c \
	   srcs/checkers/check_read_argv.c \
	   srcs/set_functions/set_resolution.c \
	   srcs/set_functions/setParForSpr.c \
	   srcs/set_functions/setAndDraw.c \
	   srcs/set_functions/set_textures.c \
	   srcs/set_functions/set_colours.c \
	   srcs/set_functions/set_dir_plane.c \
	   srcs/set_functions/make_map.c \
	   srcs/set_functions/countComa.c \
	   srcs/set_functions/setListOfSprite.c \
	   srcs/set_functions/setPlayer.c \
	   srcs/init_structs.c \
	   srcs/init_structs2.c \

OBJS = $(SRCS:.c=.o)
CC = gcc
RM = rm -rf
CFLAGS = -g -I
MACFLAGS = -framework OpenGL -framework Appkit
all:	$(NAME)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)
$(NAME):	$(OBJS)
		@make bonus -C libft
		@make -C minilibx_mms_20200219
		@mv minilibx_mms_20200219/libmlx.dylib .
		$(CC) $(CFLAGS) $(MACFLAGS) -o $(NAME) libmlx.dylib ./libft/libft.a $(OBJS)  

clean:		
		$(RM) $(OBJS)
		@make clean -C libft
		@make clean -C minilibx_mms_20200219
		$(RM)  libmlx.dylib
fclean:		clean
		$(RM) $(NAME) screenshot.bmp
		@make fclean -C libft
re:		fclean all
.PHONY:		all clean fclean re