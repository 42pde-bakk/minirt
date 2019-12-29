# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: pde-bakk <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2019/12/02 17:36:51 by pde-bakk       #+#    #+#                 #
#    Updated: 2019/12/29 16:32:27 by pde-bakk      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

SRC = minirt.c parsing.c objects.c

OBJ = $(SRC:.c=.o)

HEADER = minirt.h

FLAGS = -Wall -Werror -Wextra

INCLUDES = includes/extra.c includes/ft_itoa_base.c includes/ft_atox_peer.c \
includes/gnl/get_next_line.c includes/gnl/get_next_line_utils.c \
-I includes/gnl/

INCOBJ = extra.o ft_itoa_base.o ft_atox_peer.o get_next_line.o get_next_line_utils.o

MAGIC = -I minilibx_mms_20191025_beta -L minilibx_mms_20191025_beta -lmlx -framework OpenGL -framework AppKit libmlx.dylib

# COLORS
PINK = \x1b[35;01m
BLUE = \x1b[34;01m
YELLOW = \x1b[33;01m
GREEN = \x1b[32;01m
RED = \x1b[31;01m
WHITE = \x1b[31;37m
RESET = \x1b[0m


all: $(NAME)

$(NAME):
	@echo "$(BLUE)Remaking Libft.a"
	@make re -C ./includes/libft
	@cp ./includes/libft/libft.a libft.a
	@echo "$(YELLOW)Linking the library"
	cp minilibx_mms_20191025_beta/libmlx.dylib libmlx.dylib
	gcc -c $(FLAGS) $(HEADER) $(SRC) $(INCLUDES)
	ar -rcs $(NAME) $(OBJ) $(INCOBJ) libft.a
	@echo "$(GREEN)Done!$(RESET)"

clean:
	@echo "$(RED)Cleaning..."
	/bin/rm -f *.o *~ *.gch

fclean: clean
	@make clean -C ./includes/libft
	/bin/rm -f libft.a
	/bin/rm -f $(NAME) libmlx.dylib

re: fclean all

bonus: re
	@echo "$(PINK)Linking bonus files"

run: re
	gcc $(MAGIC) miniRT libft.a
	@echo "$(PINK)bitch"
	/bin/rm -f *.o *~ *.gch
	./a.out example.rt
