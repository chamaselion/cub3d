NAME 	= cub3d
SRC_DIR = sources
OBJ_DIR = obj

SRC = $(SRC_DIR)/main/cub3d_main.c \
		$(SRC_DIR)/main/player_movement.c \
		$(SRC_DIR)/main/rendering.c \
		$(SRC_DIR)/main/raycast.c \
		$(SRC_DIR)/main/texture.c \
		$(SRC_DIR)/main/wall_drawing.c \
		$(SRC_DIR)/main/utils.c \
		$(SRC_DIR)/checkers/checker.c \
		$(SRC_DIR)/parsing/parsing.c \
		$(SRC_DIR)/parsing/parsing_utils.c

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(SRC_DIR) -Iincludes -g -IMLX42/include -ILIBFT

LIB = LIBFT/libft.a

MLX42_DIR = MLX42
MLX42_BUILD = $(MLX42_DIR)/build
MLX42_LIB = $(MLX42_BUILD)/libmlx42.a
MLX42_FLAGS = -L$(MLX42_BUILD) -lmlx42 -lm -lpthread -ldl -lglfw

all: mlx $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(MLX42_LIB):
	@if [ ! -d "$(MLX42_DIR)" ]; then git clone https://github.com/codam-coding-college/MLX42.git $(MLX42_DIR); fi
	@cd $(MLX42_DIR) && cmake -B build && cmake --build build

mlx: $(MLX42_LIB)

$(NAME): $(OBJ)
	@$(MAKE) -C LIBFT
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(MLX42_FLAGS) $(LIB)

$(LIB):
	@$(MAKE) -C LIBFT

clean:
	rm -rf $(OBJ_DIR)
	@$(MAKE) -C LIBFT clean

cleanmlx:
	@rm -rf MLX42
	@echo "MLX42 folder is deleted!"

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C LIBFT fclean

re: fclean all

.PHONY: all clean fclean re mlx cleanmlx