# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlize <vlize@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/03/31 09:31:19 by vlize             #+#    #+#              #
#    Updated: 2016/03/25 12:02:04 by vlize            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rt

SRC =	main.c init.c error.c debug.c create_list.c parser.c parsing_func.c \
			raytracer.c general_func.c get_color.c find_intersect.c object_1.c \
			object_2.c rotation.c sub_function.c normal.c calc_color.c menu.c \
			reflection.c post_treatment.c object_3.c ray_collision.c free.c \
			csg.c csg_create.c csg_union.c csg_difference.c csg_intersection.c \
			csg_list.c is_in_shadow.c free2.c

LIB =	-L ./libft/ -lft \
		-lmlx -lm \
		-framework OpenGL -framework AppKit

INC =	-I ./include/ \
		-I /usr/local/include/ \
		-I /System/Library/Frameworks/Tk.framework/Headers/

OBJ = $(SRC:%.c=obj/%.o)

SRC_PATH = ./src/

OBJ_PATH = ./obj/

CMP = gcc -Wall -Wextra -Werror

.PHONY: all clean fclean re

all : obj $(NAME)

obj:
		@ mkdir obj

$(NAME) : $(OBJ)
		@ make -C libft/
		@ $(CMP) -o $(NAME) $(OBJ) $(LIB)
		@ echo "\x1b[32m>make all : \tOK\x1b[0m"

obj/%.o: $(SRC_PATH)/%.c
		@ $(CMP) $(INC) -o $@ -c $<

clean :
		@ make -C libft/ clean
		@ rm -rf obj
		@ echo "\x1b[32m>make clean :\tOK\x1b[0m"

fclean : clean
		@ make -s -C libft/ fclean
		@ rm -rf $(NAME)
		@ echo "\x1b[32m>make fclean :\tOK\x1b[0m"

re : fclean all
		@ echo "\x1b[32m>make re :  \tOK\x1b[0m"
