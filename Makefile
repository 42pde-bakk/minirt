# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: Peer de Bakker <pde-bakk@student.codam.      +#+                      #
#                                                    +#+                       #
#    Created: 2019/12/02 17:36:51 by pde-bakk      #+#    #+#                  #
#    Updated: 2020/04/24 16:46:31 by peer          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

SRC_DIR = ./src
RAY_DIR = $(SRC_DIR)/rays/
PARSING_DIR = $(SRC_DIR)/parsing/
OBJECTS_DIR = $(SRC_DIR)/objects/
LIGHT_DIR = $(SRC_DIR)/lighting/
MATH_DIR = $(SRC_DIR)/math/
INTERACTION_DIR = $(SRC_DIR)/interaction/
GNL_DIR = ./gnl/
LIBFT_DIR = ./libft/
EXTRA_DIR = $(SRC_DIR)/extra/
MLX_DIR = ./minilibx_mms_20200219/
LIBMLX = libmlx.dylib
ifdef LINUX
 MLX_DIR = ./minilibx-linux-new/
 LIBMLX = libmlx.a
endif
HEADER = -I ./includes/

SRC = minirt.c newframe.c freebwilbers.c bmp.c get_uvimg.c
RAY = rays.c ndcxy.c put_rgb.c render_pixel.c
PARSING = parsing.c parse_camera.c parse_cylinder.c parse_light.c \
	parse_plane.c parse_resolution.c parse_sphere.c parse_square.c \
	parse_tcol.c parse_triangle.c
OBJECTS = objects.c find_cylinder.c find_plane.c find_sphere.c find_square.c \
	find_triangle.c uvmapping.c rainbow.c wave.c find_cylinder_caps.c bumpmapping.c
LIGHT = lighting.c obstacles.c obstacle_cylinder.c obstacle_plane.c \
	obstacle_sphere.c obstacle_square.c obstacle_triangle.c
MATH = colour.c degrad.c mat4_angles.c matrices.c quaternions.c quaternions2.c \
	rotations.c vectors_adv.c vectors.c mat4_lookat.c colour_checks.c
INTERACTION = click_object.c click_cylinder_plane.c click_sphere_square.c \
	readinput.c	obj_edit_properties.c get_click_info.c obj_edit_props2.c \
	camera_action.c obj_edit_props_square.c mouseinput.c \
	obj_edit_props_triangle.c
GNL = get_next_line.c get_next_line_utils.c
LIBFT = ft_lstmap_bonus.c ft_strjoin.c ft_atoi.c ft_lstnew_bonus.c \
ft_strlcat.c ft_bzero.c ft_lstsize_bonus.c ft_strlcpy.c ft_calloc.c \
ft_memccpy.c ft_strlen.c ft_isalnum.c ft_memchr.c ft_strmapi.c ft_isalpha.c \
ft_memcmp.c ft_strncmp.c ft_isascii.c ft_memcpy.c ft_strnstr.c ft_isdigit.c \
ft_memmove.c ft_strrchr.c ft_isprint.c ft_memset.c ft_strtrim.c ft_itoa.c \
ft_putchar_fd.c ft_substr.c ft_lstadd_back_bonus.c ft_putendl_fd.c \
ft_tolower.c ft_lstadd_front_bonus.c ft_putnbr_fd.c ft_toupper.c \
ft_lstclear_bonus.c ft_putstr_fd.c ft_lstdelone_bonus.c ft_split.c \
ft_lstiter_bonus.c ft_strchr.c ft_lstlast_bonus.c ft_strdup.c


EXTRA = ft_itoa_base.c ft_atox_peer.c ft_putstr_int.c extra.c

FILES = $(addprefix $(SRC_DIR)/, $(SRC))
FILES += $(addprefix $(RAY_DIR), $(RAY))
FILES += $(addprefix $(PARSING_DIR), $(PARSING))
FILES += $(addprefix $(OBJECTS_DIR), $(OBJECTS))
FILES += $(addprefix $(MATH_DIR), $(MATH))
FILES += $(addprefix $(LIGHT_DIR), $(LIGHT))
FILES += $(addprefix $(GNL_DIR), $(GNL))
FILES += $(addprefix $(LIBFT_DIR), $(LIBFT))
FILES += $(addprefix $(EXTRA_DIR), $(EXTRA))
FILES += $(addprefix $(INTERACTION_DIR), $(INTERACTION))

#MAX_RESX := $(shell displayplacer list | grep "current mode" | \
awk -F '[:x]' '/mode/{print$$3}')
#MAX_RESY := $(shell displayplacer list | grep "current mode" | \
awk -F '[:xc]' '/mode/{print$$4}')

FLAGS = #-Wall -Werror -Wextra -pedantic -g
BONUS_FLAGS = -D BONUS=0 -D THREADCOUNT=1
ifdef SPEED
FLAGS += -Ofast -march=native
endif
ifdef DEBUG
 FLAGS += -g -fsanitize=address -fno-omit-frame-pointer
endif
ifdef UV
 FLAGS += -D UV=$(UV)
endif
ifdef MOUSEROTATE
 FLAGS += -D MOUSEROTATE=1
endif
ifdef SEPIA
 FLAGS += -D SEPIA=1
endif
ifdef AA
 FLAGS += -D ANTIALIASING=1
endif
ifdef STEREOSCOPY
 FLAGS += -D STEREOSCOPY=1
endif
ifdef RAINBOW
 FLAGS += -D RAINBOW=1
endif
ifdef WAVE
 FLAGS += -D WAVE=1
endif
ifdef BUMP
 FLAGS += -D BUMP=1
endif

MAGIC = -L minilibx_mms_20200219 -lmlx -framework AppKit
ifdef LINUX
 MAGIC = -L $(MLX_DIR) -lmlx
 FLAGS += -D LINUX=1
endif

# COLORS
PINK = \x1b[35;01m
BLUE = \x1b[34;01m
YELLOW = \x1b[33;01m
GREEN = \x1b[32;01m
RED = \x1b[31;01m
WHITE = \x1b[31;37m
RESET = \x1b[0m


all: $(NAME)

$(NAME): $(FILES)
	@$(shell ./textures/getpic exec >/dev/null exec 2>/dev/null)
	@echo "$(BLUE)Remaking libft.a"
	@make re -C $(LIBFT_DIR)
	@cp $(LIBFT_DIR)/libft.a .
	@echo "$(YELLOW)Making MiniLibX"
	@chmod +x $(MLX_DIR)mlx.h
	@cp $(MLX_DIR)/mlx.h includes/
	@make -C $(MLX_DIR)
	@cp $(MLX_DIR)/$(LIBMLX) .
	@gcc $(FLAGS) $(BONUS_FLAGS) $(HEADER) $(MAGIC) $(LIBMLX) $(FILES) -o $(NAME) -lmlx -lXext -lX11 -pthread -lm -lz

clean:
	@echo "$(RED)Cleaning..."
	/bin/rm -f *.o *~ *.gch

fclean: clean
	@make fclean -C ./libft
	/bin/rm -f libft.a
	/bin/rm -f includes/mlx.h
	/bin/rm -f $(NAME) libmlx.dylib

re: fclean all

fuckingclean: fclean
	/bin/rm -f \#*\# a.out
	/bin/rm -rf *.dSYM
	@make fclean -C ./libft

bonus: BONUS_FLAGS = -D BONUS=1 -D THREADCOUNT=4
bonus: re
	@echo "$(PINK)Linking bonus files"

run: re
	@make clean
	@echo "$(PINK)bitch"
	./miniRT ./scenes/peer.rt

