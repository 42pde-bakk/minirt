# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: Peer de Bakker <pde-bakk@student.codam.      +#+                      #
#                                                    +#+                       #
#    Created: 2019/12/02 17:36:51 by pde-bakk       #+#    #+#                 #
#    Updated: 2020/01/21 17:39:33 by pde-bakk      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

SRC = minirt.c parsing.c objects.c parseobjects.c vectors.c rays.c \
sphere.c planesquare.c readinput.c lighting.c colour.c obstacles.c matrices.c \
vectors_adv.c degrad.c quaternion.c mat4_angles.c

MAX_RESX := $(shell displayplacer list | grep "current mode" | awk -F '[:x]' '/mode/{print$$3}')
MAX_RESY := $(shell displayplacer list | grep "current mode" | awk -F '[:xc]' '/mode/{print$$4}')

OBJ = $(SRC:.c=.o)

HEADER = minirt.h

FLAGS = -Wall -Werror -Wextra -g
ifdef SPEED
FLAGS += -O3
endif

ifdef DEBUG
 FLAGS += -fsanitize=address
endif

INCLUDES = includes/extra.c includes/ft_itoa_base.c includes/ft_atox_peer.c \
includes/gnl/get_next_line.c includes/gnl/get_next_line_utils.c

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
	@make -C ./minilibx_mms_20191025_beta/
	cp minilibx_mms_20191025_beta/libmlx.dylib libmlx.dylib
	@echo MY_RESX is $(MAX_RESX)
	@echo MY_RESY is $(MAX_RESY)
	gcc -c -D MAX_RESX=$(MAX_RESX) -D MAX_RESY=$(MAX_RESY) $(FLAGS) $(HEADER) $(SRC) $(INCLUDES)
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

fuckingclean: fclean
	/bin/rm -f \#*\# a.out
	/bin/rm -rf *.dSYM
	@make fclean -C ./includes/libft

bonus: re
	@echo "$(PINK)Linking bonus files"

run: re
	gcc $(FLAGS) $(MAGIC) -o miniRT miniRT libft.a
	@make clean
	@echo "$(PINK)bitch"
	./miniRT example.rt
