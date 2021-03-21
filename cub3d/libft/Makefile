NAME	= libft.a

SFILES	= ft_memset.c\
			 ft_bzero.c\
			 ft_memcpy.c\
			 ft_memccpy.c\
			 ft_memmove.c\
			 ft_memchr.c\
			 ft_memcmp.c\
			 ft_strlen.c\
			 ft_strlcpy.c\
			 ft_strlcat.c\
			 ft_strchr.c\
			 ft_strrchr.c\
			 ft_strnstr.c\
			 ft_strncmp.c\
			 ft_atoi.c\
			 ft_isalpha.c\
			 ft_isdigit.c\
			 ft_isalnum.c\
			 ft_isascii.c\
			 ft_isprint.c\
			 ft_toupper.c\
			 ft_tolower.c\
			 ft_calloc.c\
			 ft_strtrim.c\
			 ft_strdup.c\
			 ft_substr.c\
			 ft_strjoin.c\
			 ft_split.c\
			 ft_itoa.c\
			 ft_strmapi.c\
			 ft_putchar_fd.c\
			 ft_putstr_fd.c\
			 ft_putendl_fd.c\
			 ft_putnbr_fd.c\
			 
SFILES_BONUS = ft_lstnew.c\
			 ft_lstadd_front.c\
			 ft_lstsize.c\
			 ft_lstlast.c\
			 ft_lstadd_back.c\
			 ft_lstdelone.c\
			 ft_lstclear.c\
			 ft_lstiter.c\
			 ft_lstmap.c\

SOBJ 	= $(SFILES:.c=.o)

SOBJ_BONUS = $(SFILES_BONUS:.c=.o)

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

HEADER = libft.h

.c.o:
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):	$(SOBJ)
			ar rc $(NAME) $(SOBJ)
			ranlib $(NAME)
			
all:		$(NAME)

bonus:		$(SOBJ) $(SOBJ_BONUS)
			ar rc $(NAME) $(SOBJ) $(SOBJ_BONUS)
			ranlib $(NAME)

clean:
			rm -rf $(SOBJ) 
			rm -rf $(SOBJ_BONUS)

fclean:		clean
			rm -rf $(NAME)

re:			fclean all

.PHONY: all, clean, fclean, re, bonus