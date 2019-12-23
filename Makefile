# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: pde-bakk <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2019/12/02 17:36:51 by pde-bakk       #+#    #+#                 #
#    Updated: 2019/12/23 16:19:09 by pde-bakk      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

SRC = minirt.c objects.c

OBJ = $(SRC:.c=.o)

HEADER = minirt.h

FLAGS = -Wall -Werror -Wextra -g

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
	@echo "$(YELLOW)Linking the library"
	gcc -c $(FLAGS) $(HEADER) $(SRC)
	ar -rc $(NAME) $(OBJ)
	@echo "$(GREEN)Done!"

clean:
	@echo "$(RED)Cleaning..."
	/bin/rm -f *.o *~ *.gch

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

bonus: re
	@echo "$(PINK)Linking bonus files"
