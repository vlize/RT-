#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlize <vlize@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/05 16:49:57 by vlize             #+#    #+#              #
#    Updated: 2014/11/26 13:32:54 by vlize            ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = libft.a

SRC = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c \
	ft_memcmp.c ft_strlen.c ft_strdup.c ft_strcpy.c ft_strncpy.c ft_strcat.c \
	ft_strncat.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strstr.c ft_ishexa.c \
	ft_strnstr.c ft_strcmp.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c \
	ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_itox.c \
	ft_putchar.c ft_putnbr.c ft_putstr.c ft_putendl.c ft_ftoa.c ft_nbrblen.c \
	ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_itoa.c ft_memalloc.c \
	ft_memdel.c ft_strdel.c ft_strnew.c ft_strsub.c ft_strjoin.c ft_strtrim.c \
	ft_strsplit.c ft_strclr.c ft_striter.c ft_striteri.c ft_strmap.c ft_itoo.c \
	ft_strmapi.c ft_strequ.c ft_strnequ.c ft_lstadd.c ft_lstnew.c ft_lstdel.c \
	ft_lstiter.c ft_lstmap.c ft_elemdel.c ft_putendn.c ft_endian.c ft_itob.c \
	ft_putendn_fd.c ft_putendc.c ft_putendc_fd.c ft_free.c ft_isspace.c \
	ft_nbrlen.c ft_nbrulen.c ft_putwchar.c ft_putwchar_fd.c ft_putwstr.c \
	ft_putwstr_fd.c ft_strwlen.c ft_iswprint.c ft_nbrxlen.c ft_putwnbr.c \
	ft_putunbr.c ft_nbrolen.c ft_unicode.c ft_putchar_fd.c ft_lstdelone.c \
	ft_isocta.c ft_unilen.c ft_nbrflen.c ft_putflt.c ft_sqrt.c get_next_line.c \
	ft_xtoi.c

OBJ = $(SRC:.c=.o)

LIB = includes/libft.h

all : $(NAME)

$(NAME) :
		@ gcc -Wall -Wextra -Werror -c $(SRC) -I ./includes/
		@ ar rc $(NAME) $(OBJ) $(LIB)
		@ ranlib $(NAME)

clean :
		@ rm -f $(OBJ)

fclean : clean
		@ rm -f $(NAME)

re : fclean all