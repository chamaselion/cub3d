NAME = cub3d
SRC_DIR = sources
OBJ_DIR = obj
SRC = $(SRC_DIR)/main/cub3d_main.c
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(SRC_DIR) -Iincludes -g
MLX42_FLAGS = -lmlx42 -lm -lpthread -ldl -lglfw

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(MLX42_FLAGS)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all