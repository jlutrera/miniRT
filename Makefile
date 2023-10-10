# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/09 11:10:11 by adpachec          #+#    #+#              #
#    Updated: 2023/10/09 19:21:16 by jutrera-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Paths
L_DIR		=	./libft/
O_DIR		=	./obj/
I_DIR		=	./include/
S_DIR		=	./srcs/

#Files
LIB_A		=	libft.a
SRCS		=	$(S_DIR)main.c \
				$(S_DIR)process_file.c \
				$(S_DIR)vec_operations1.c \
				$(S_DIR)vec_operations2.c \
				$(S_DIR)vec_operations3.c \
				$(S_DIR)ray.c \
				$(S_DIR)print_errors.c \
				$(S_DIR)my_hooks.c \
				$(S_DIR)color.c \
				$(S_DIR)process_img.c \
				$(S_DIR)sphere.c \
				$(S_DIR)plane.c \
				$(S_DIR)cylinder.c \
				$(S_DIR)cylinder2.c \
				$(S_DIR)light_shadow.c \
				$(S_DIR)parser.c \
				$(S_DIR)parser_utils.c \
				$(S_DIR)parser_gets.c \
				$(S_DIR)parser_loads.c \
				$(S_DIR)parser_lists.c

OBJS		=	$(patsubst $(S_DIR)%, $(O_DIR)%, $(SRCS:.c=.o))
HEADER		=	$(I_DIR)miniRT.h \
				$(I_DIR)errors.h
LIB_N		=	$(L_DIR)$(LIB_A)

# Constant strings
NAME		=	miniRT
RM 			=	rm -rf
LIBFLAGS	=	-Llibft -lft
W_FLAGS		=	-Wall -Wextra -Werror -Wpedantic -g3 -Wshadow
#LEAKS		=	-fsanitize=address

ifeq ($(shell uname -s), Darwin)
	MLXFLAG = -lmlx -framework OpenGL -framework AppKit
else
	MLXFLAG	= -Lusr/lib -Lmlx_linux -lmlx -lXext -lX11 -lm -lbsd -Imlx_linux
endif

#  Colors
CYAN		=	\033[1;36m
YELLOW		=	\033[1;33m
GRAY		=	\033[2;37m
RESET		=	\033[0m

# Rules
all			:	$(NAME)

$(O_DIR)	:
				@echo "Creating program $(YELLOW)$(NAME)$(RESET)"
				@mkdir -p $(O_DIR)

$(O_DIR)%.o	:	$(S_DIR)%.c $(HEADER)
				@echo "$(GRAY)Compiling $@ ! $(RESET)"
				@$(CC) $(W_FLAGS) -c $< -o $@

$(NAME) 	:	$(LIB_N) $(O_DIR) $(OBJS)
				@echo "$(YELLOW)Linking object files ! ... $(RESET)\c"
				@$(CC) $(OBJS) $(LEAKS) $(LIBFLAGS) $(MLXFLAG) -o $(NAME)
				@echo "$(NAME) created successfully !"

$(LIB_N)	:		
				@echo "Creating library $(YELLOW) $(LIB_A) $(RESET)"
				@$(MAKE) --no-print-directory -C $(L_DIR)

clean		:	
				@$(MAKE) --no-print-directory clean -C $(L_DIR) 
				@$(RM) $(O_DIR)
				@echo "$(CYAN)Deleted all the object files$(RESET)"

fclean		:	clean
				@$(MAKE) --no-print-directory fclean -C $(L_DIR)
				@$(RM) $(NAME)
				@echo "$(CYAN)Deleted all the exec files$(RESET)"

re			:	fclean all

.PHONY		:	all clean fclean re