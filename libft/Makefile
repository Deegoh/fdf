# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/11 18:54:17 by tpinto-m          #+#    #+#              #
#   Updated: 2022/03/22 16:14:53 by tpinto-m         ###   ########.fr       # #
#                                                                              #
# **************************************************************************** #

CC = cc
NAME = libft.a
CFLAGS = -Wall -Wextra -Werror
SRC = ft_putnbr_fd.c\
	  ft_putendl_fd.c\
	  ft_putstr_fd.c\
	  ft_putchar_fd.c\
	  ft_striteri.c\
	  ft_strmapi.c\
	  ft_itoa.c\
	  ft_split.c\
	  ft_strtrim.c\
	  ft_strjoin.c\
	  ft_substr.c\
	  ft_strdup.c\
	  ft_calloc.c\
	  ft_atoi.c\
	  ft_strnstr.c\
	  ft_strlcat.c\
      ft_strlcpy.c\
      ft_strncmp.c\
      ft_strrchr.c\
      ft_strchr.c\
      ft_toupper.c\
      ft_tolower.c\
      ft_isprint.c\
	  ft_isspace.c\
      ft_isascii.c\
      ft_isalnum.c\
      ft_isdigit.c\
      ft_isalpha.c\
	  ft_strlen.c\
	  ft_memcmp.c\
	  ft_memchr.c\
	  ft_memmove.c\
	  ft_memccpy.c\
	  ft_memcpy.c\
	  ft_bzero.c\
	  ft_memset.c

BONUS = ft_lstmap.c\
		ft_lstiter.c\
		ft_lstclear.c\
		ft_lstdelone.c\
		ft_lstadd_back.c\
		ft_lstlast.c\
		ft_lstsize.c\
		ft_lstadd_front.c\
		ft_lstnew.c

SRCGNL = get_next_line.c

OBJ = $(SRC:.c=.o)
OBJBONUS = $(BONUS:.c=.o)
OBJGNL = $(SRCGNL:.c=.o)

.PHONY: all clean fclean re bonus gnl

all: $(NAME)

$(NAME): bonus gnl $(OBJ)
	ar -rcs $(NAME) $(OBJ)

bonus: $(OBJBONUS)
	ar -rcs $(NAME) $(OBJBONUS)

gnl: $(OBJGNL)
	ar -rcs $(NAME) $(OBJGNL)

clean:
	rm -rf $(OBJ)
	rm -rf $(OBJBONUS)
	rm -rf $(OBJGNL)

fclean: clean
	rm -rf $(NAME)

re: fclean all
