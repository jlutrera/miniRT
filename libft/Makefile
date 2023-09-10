# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jutrera- <jutrera-@student.42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/27 18:05:52 by jutrera-          #+#    #+#              #
#    Updated: 2022/10/15 11:35:42 by jutrera-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -Wpedantic -fsanitize=address -O3

I_DIR		=	include/
O_DIR		=	obj/
S_DIR		=	./srcs/
SRCS		=	./srcs/ft_atoi.c 		./srcs/ft_bzero.c 		 ./srcs/ft_calloc.c \
				./srcs/ft_digitutils.c	./srcs/ft_isalnum.c 	 ./srcs/ft_isalpha.c \
				./srcs/ft_isascii.c 	./srcs/ft_isdigit.c 	 ./srcs/ft_isprint.c \
				./srcs/ft_itoa.c 		./srcs/ft_lstadd_front.c ./srcs/ft_lstclear.c \
				./srcs/ft_lstdelone.c 	./srcs/ft_lstiter.c 	 ./srcs/ft_lstlast.c \
				./srcs/ft_lstmap.c 		./srcs/ft_lstnew.c		 ./srcs/ft_lstsize.c \
				./srcs/ft_memchr.c 		./srcs/ft_memcmp.c 		 ./srcs/ft_memcpy.c \
				./srcs/ft_memmove.c 	./srcs/ft_memset.c 		 ./srcs/ft_printf_utils.c \
				./srcs/ft_printf.c		./srcs/ft_putchar_fd.c 	 ./srcs/ft_putchar.c \
				./srcs/ft_putdigit.c 	./srcs/ft_putendl_fd.c 	 ./srcs/ft_puthex.c \
				./srcs/ft_putnbr_fd.c 	./srcs/ft_putpointer.c 	 ./srcs/ft_putstr_fd.c \
				./srcs/ft_putstr.c 		./srcs/ft_putunsigned.c  ./srcs/ft_read_flags.c \
				./srcs/ft_split.c 		./srcs/ft_strchr.c 		 ./srcs/ft_strcmp.c \
				./srcs/ft_strdup.c 		./srcs/ft_striteri.c 	 ./srcs/ft_strjoin.c \
				./srcs/ft_strjoin2.c 	./srcs/ft_strlcat.c 	 ./srcs/ft_strlcpy.c \
				./srcs/ft_strlen.c 		./srcs/ft_strlen2.c 	 ./srcs/ft_strmapi.c \
				./srcs/ft_strncmp.c 	./srcs/ft_strnstr.c 	 ./srcs/ft_strrchr.c \
				./srcs/ft_strtrim.c 	./srcs/ft_substr.c 		 ./srcs/ft_tolower.c \
				./srcs/ft_toupper.c		./srcs/get_next_line.c	 ./srcs/get_next_line_utils.c
OBJS		=	$(patsubst $(S_DIR)%, $(O_DIR)%, $(SRCS:.c=.o))

NRM 		= 	\033[0;39m
RED 		= 	\033[0;91m
GREEN 		= 	\033[0;92m
YELLOW 		= 	\033[0;93m
BLUE 		= 	\033[0;94m

all			:	${NAME}

$(O_DIR)	:
				@mkdir -p $(O_DIR)

$(O_DIR)%.o	:	$(S_DIR)%.c
				@echo "$(BLUE)Compiling $@ !... $(NRM)\c"
				@${CC} ${CFLAGS} -I$(I_DIR) -c $< -o $@
				@echo "$(GREEN)OK$(NRM)"

${NAME}		:	$(O_DIR) $(OBJS)
				@echo "$(YELLOW)Linking object files ! $(NRM)\c"
				@ar rcs ${NAME} ${OBJS}
				@echo "$(GREEN)SUCCESS !$(NRM)"
				@ranlib $(NAME)
				@echo "libft.a created successfully !"

clean		:
				@rm -Rf $(O_DIR)/

fclean		:	clean
				@rm -f ${NAME}

re			:	fclean all

.PHONY		:	all clean fclean re
