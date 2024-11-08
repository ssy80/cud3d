NAME = cub3D
NAME_BONUS = cub3D_bonus
CC = cc
CFLAGS = -g -Wall -Wextra -Werror -I .
MLXFLAGS = -Lminilibx-linux -lmlx_Linux -lX11 -lXext -lm
HELPER_DIR = ./helper
RM = rm -f
HEADER = cub3D.h
MLX = ./minilibx-linux

SRC = cub3D.c
OBJ = $(SRC:.c=.o)
HELPER = $(wildcard $(HELPER_DIR)/*.c)
HELPER_OBJ = $(HELPER:.c=.o)
SRC_BONUS = cub3D_bonus.c
OBJ_BONUS = $(SRC_BONUS:.c=.o)

all : $(NAME)

bonus : $(NAME_BONUS)

$(NAME_BONUS) : $(OBJ_BONUS) $(HELPER_OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(MLXFLAGS)

$(NAME) : $(HELPER_OBJ) $(OBJ)
	$(MAKE) -C $(MLX) all
	$(CC) $(CFLAGS) $^ -o $@ $(MLXFLAGS)

$(HELPER_DIR)/%.o : $(HELPER_DIR)/%.c $(HEADER)
	$(CC) -c $(CFLAGS) $< -o $@ 

clean :
	$(RM) $(HELPER_OBJ) $(OBJ) $(OBJ_BONUS)
	$(MAKE) -C $(MLX) clean

fclean : clean
	$(RM) $(NAME) $(NAME_BONUS)

re : fclean all

run : $(NAME)
	./$(NAME)

debug : $(NAME)
	gdb ./$(NAME) --tui

nm : $(NAME)
	nm -u ./$(NAME)

run: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) 

norm :
	norminette $(HELPER_DIR)/*.c
	norminette *.c
	norminette *.h

run :
	./$(NAME) test.cub