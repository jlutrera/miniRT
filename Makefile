# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/09 11:10:11 by adpachec          #+#    #+#              #
#    Updated: 2023/10/15 21:15:19 by adpachec         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Paths
L_DIR		=	./libft/
O_DIR		=	./obj/
I_DIR		=	./include/
S_DIR		=	./mandatory/
BO_DIR		=	./obj_bonus/
BS_DIR		=	./bonus/

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

B_SRCS		=	$(BS_DIR)vec_operations1_bonus.c \
				$(BS_DIR)vec_operations2_bonus.c \
				$(BS_DIR)vec_operations3_bonus.c \
				$(BS_DIR)ray_bonus.c \
				$(BS_DIR)print_errors_bonus.c \
				$(BS_DIR)my_hooks_bonus.c \
				$(BS_DIR)color_bonus.c \
				$(BS_DIR)cylinder2_bonus.c \
				$(BS_DIR)parser_utils_bonus.c \
				$(BS_DIR)parser_gets_bonus.c \
				$(BS_DIR)process_file_bonus.c \
				$(BS_DIR)main_bonus.c \
				$(BS_DIR)process_img_bonus.c \
				$(BS_DIR)parser_bonus.c \
				$(BS_DIR)parser_loads_bonus.c \
				$(BS_DIR)parser_lists_bonus.c \
				$(BS_DIR)triangle_bonus.c \
				$(BS_DIR)light_shadow_bonus.c \
				$(BS_DIR)sphere_bonus.c \
				$(BS_DIR)plane_bonus.c \
				$(BS_DIR)cylinder_bonus.c \
				$(BS_DIR)cone_bonus.c \
				$(BS_DIR)cone2_bonus.c

OBJS		=	$(patsubst $(S_DIR)%, $(O_DIR)%, $(SRCS:.c=.o))
B_OBJS		=	$(patsubst $(BS_DIR)%, $(BO_DIR)%, $(B_SRCS:.c=.o))
HEADER		=	$(I_DIR)miniRT.h
B_HEADER	=	$(I_DIR)miniRT_bonus.h
LIB_N		=	$(L_DIR)$(LIB_A)

# Constant strings
NAME		=	miniRT
B_NAME		=	miniRT
RM 			=	rm -rf
LIBFLAGS	=	-Llibft -lft
W_FLAGS		=	-Wall -Wextra -Werror -Wpedantic -g3 -Wshadow
LEAKS		=	-fsanitize=address

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
bonus		:	$(B_NAME)

$(O_DIR)	:
				@echo "Creating program $(YELLOW)$(NAME)$(RESET)"
				@mkdir -p $(O_DIR)
$(BO_DIR)	:
				@echo "Creating bonus program $(YELLOW)$(B_NAME)$(RESET)"
				@mkdir -p $(BO_DIR)

$(O_DIR)%.o	:	$(S_DIR)%.c $(HEADER)
				@echo "$(GRAY)Compiling $@ ! $(RESET)"
				@$(CC) $(W_FLAGS) -c $< -o $@
$(BO_DIR)%.o:	$(BS_DIR)%.c $(B_HEADER)
				@echo "$(GRAY)Compiling $@ ! $(RESET)"
				@$(CC) $(W_FLAGS) -c $< -o $@

$(NAME) 	:	$(LIB_N) $(O_DIR) $(OBJS)
				@echo "$(YELLOW)Linking object files ! ... $(RESET)\c"
				@$(CC) $(OBJS) $(LEAKS) $(LIBFLAGS) $(MLXFLAG) -o $(NAME)
				@echo "$(NAME) created successfully !"
$(B_NAME) 	:	$(LIB_N) $(BO_DIR) $(B_OBJS)
				@echo "$(YELLOW)Linking object files ! ... $(RESET)\c"
				@$(CC) $(B_OBJS) $(LEAKS) $(LIBFLAGS) $(MLXFLAG) -o $(B_NAME)
				@echo "$(B_NAME) created successfully !"
$(LIB_N)	:		
				@echo "Creating library $(YELLOW) $(LIB_A) $(RESET)"
				@$(MAKE) --no-print-directory -C $(L_DIR)

clean		:	
			 	@$(MAKE) --no-print-directory clean -C $(L_DIR) 
				@$(RM) $(O_DIR)
				@$(RM) $(BO_DIR)
				@echo "$(CYAN)Deleted all the object files$(RESET)"

fclean		:	clean
				@$(MAKE) --no-print-directory fclean -C $(L_DIR)
				@$(RM) $(NAME)
				@$(RM) $(B_NAME)
				@echo "$(CYAN)Deleted all the exec files$(RESET)"

re			:	fclean all
re_bonus	:	fclean bonus
.PHONY		:	all clean fclean re bonus re_bonus