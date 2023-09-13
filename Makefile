SRCS = main.c ./srcs/ft_strjoin.c ./srcs/error.c ./srcs/ft_atoi.c ./srcs/ft_itoa.c ./srcs/ft_printf.c ./srcs/ft_split.c ./srcs/ft_strdup.c \
	./srcs/get_next_line.c ./srcs/get_next_line_utils.c ./srcs/ft_strtrim.c ./srcs/ft_substr.c ./validation/validation.c ./validation/validation2.c \
	./validation/validation3.c ./validation/fill_type.c ./config/p_move.c ./config/drawing.c ban.c

SRCS_TEST = main_mlx_test.c #//! if you want to test mlx library


# OBJS			= $(SRCS_TEST:.c=.o)
OBJS			= $(SRCS:.c=.o)#//! CHANGE SRCS TO SRCS_TEST IF YOU WANT TO SEE SIMPLE EXAMPLE OF MLX LIBRARY
CC				= cc
RM				= rm -f
GLFW			= $(shell brew --prefix glfw)
MLX_FLAG		= ~/MLX42/build/libmlx42.a -I ~/MLX42/include -Iinclude -lglfw -L $(GLFW)/lib/ -framework Cocoa -framework OpenGL -framework IOKit
LIBS            = -Wall -Wextra -Werror #-fsanitize=address  -g
NAME			= cub3D


%.o : %.c 
		@$(CC) $(CFLAGS) -I ~/MLX42/include -c $< -o $@

all:		cube_3d_logo	$(NAME) 

$(NAME):	cube_3d_logo	$(OBJS)
			@cc $(LIBS) $(OBJS) $(MLX_FLAG) -o $(NAME)
			@echo "\033[92m\033[92m✅cub3D GENERATED YOU CAN STARTED✅\033[0m"
			@echo "\033[92m🎮 USE ./cub3D <MAP FILE NAME> 🎮"
clean:
				@$(RM) $(OBJS) 
				@echo "\033[92m\033[31m Delete object files🗑\033[31m"
			
fclean:			clean
				@$(RM) $(NAME)
				@echo "\033[92m\033[31m Delete exucted file🗑\033[31m"

re:				fclean $(NAME)

test: re
				@echo "\033[92m\033[31m 🪄TESTING MAP1🪄\033[31m"
				@./cub3D ./maps/map1.cub
test2: re
				@echo "\033[92m\033[31m🪄 TESTING MAP2🪄\033[31m"
				@./cub3D ./maps/map3.cub


cube_3d_logo:

	@echo "\033[92m ██████╗██╗   ██╗██████╗ ███████╗\033[0m██████╗ ██████╗"
	@echo "\033[92m██╔════╝██║   ██║██╔══██╗██╔════╝\033[0m╚════██╗██╔══██╗"
	@echo "\033[92m██║     ██║   ██║██████╔╝█████╗  \033[0m █████╔╝██║  ██║"
	@echo "\033[92m██║     ██║   ██║██╔══██╗██╔══╝  \033[0m ╚═══██╗██║  ██║"
	@echo "\033[92m╚██████╗╚██████╔╝██████╔╝███████ \033[0m██████╔╝██████╔╝"
	@echo "\033[92m ╚═════╝ ╚═════╝ ╚═════╝ ╚══════╝\033[0m╚═════╝ ╚═════╝"
	@echo "\033[92m⌛CREATING .O FILES AND SO_LONG⌛\033[0m"


.PHONY: all fclean clean re cube_3d_logo
