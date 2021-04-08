NAME = cub3d
SRCS = setBasRayPar.c \
	   untextured.c \
	   get_next_line.c \
	   drawSprite.c \
	   drawFOV.c \

OBJS = $(SRCS:.c=.o)
CC = clang
RM = rm -rf
CFLAGS = -g
MACFLAGS = -framework OpenGL -framework Appkit
all:		$(NAME)
%.o: %.c
	$(CC) $(CFLAGS) -c ./libft/ ./minilibx_mms_20200219/ $< -o $(<:.c=.o)
$(NAME):	$(OBJS)
		@make bonus -C libft
		@make -C minilibx_mms_20200219
		@mv minilibx_mms_20200219/libmlx.dylib .
		$(CC) $(CFLAGS) $(MACFLAGS) -o $(NAME) libmlx.dylib ./libft/libft.a $(OBJS)  
				
clean:		
		$(RM) $(OBJS)
		@make clean -C libft
		@make clean -C minilibx_mms_20200219
fclean:		clean
		$(RM) $(NAME) cub3d.bmp
		@make fclean -C libft
re:		fclean all
.PHONY:		all clean fclean re