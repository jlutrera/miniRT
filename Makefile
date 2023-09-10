# Paths
L_DIR		=	./libft/
O_DIR		=	./obj/
I_DIR		=	./include/
S_DIR		=	./srcs/

#Files
LIB_A		=	libft.a
SRCS		=	./srcs/process_file.c ./srcs/main.c 
OBJS		=	$(patsubst $(S_DIR)%, $(O_DIR)%, $(SRCS:.c=.o))
HEADER		=	$(I_DIR)miniRT.h
LIB_N		=	$(L_DIR)$(LIB_A)

# Constant strings
NAME		=	miniRT
RM 			=	rm -rf
LIBFLAGS	=	-Llibft -lft
LEAKS		=	-fsanitize=address
W_FLAGS		=	-Wall -Wextra -Werror -Wpedantic -g3

#Para Windows
MLXFLAGS	= 	-Lusr/lib -lmlx -lXext -lX11 -lm -lbsd
INCL		=	-Imlx_linux -I$(HEADER)

#Para Mac
#MLXFLAGS	=	-lmlx -framework OpenGL -framework AppKit
#INCL		=	-I$(HEADER)

#  Colors
CYAN		=	\033[1;36m
YELLOW		=	\033[1;33m
GREEN		=	\033[0;32m
BLUE 		= 	\033[0;94m
RESET		=	\033[0m

# Rules
all			:	$(NAME)

$(O_DIR)	:
				@echo "Creating program $(YELLOW)$(NAME)$(RESET)"
				@mkdir -p $(O_DIR)

$(O_DIR)%.o	:	$(S_DIR)%.c
				@echo "$(BLUE)Compiling $@ ! $(RESET)\c"
#@$(CC) $(W_FLAGS) -c $< -o $@
				@$(CC)  -c $< -o $@
				@echo "... $(GREEN)OK$(RESET)" 

$(NAME) 	:	$(LIB_N) $(O_DIR) $(OBJS) $(HEADER)
				@echo "$(YELLOW)Linking object files ! $(RESET)\c"
				@$(CC) $(OBJS) $(LEAKS) $(LIBFLAGS) $(MLXFLAGS) $(INCL) -o $(NAME)
				@echo "$(GREEN)SUCCESS !$(RESET)"
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