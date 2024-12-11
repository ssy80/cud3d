DIR			= .
DIR_ERR = ./err
DIR_HELPER = ./helper
DIR_LOAD = ./load
DIR_GNL = ./gnl
SRC			= ${DIR}/cub3d.c \
					${DIR}/event_handler.c \
					${DIR}/image_helper.c \
					${DIR}/draw_helper.c \
					${DIR}/movement.c \
					${DIR}/init.c \
					${DIR}/player_helper.c \
					${DIR}/ray_casting.c \
					${DIR_GNL}/get_next_line.c \
					${DIR_GNL}/get_next_line_utils.c \
					${DIR_ERR}/err_manage.c\
					${DIR_ERR}/err_mapcheck.c\
					${DIR_ERR}/err_smartptr.c\
					${DIR_ERR}/err_color.c\
					${DIR_LOAD}/loadmap.c\
					${DIR_LOAD}/loadvar.c\
					${DIR_HELPER}/char2dlen.c\
					${DIR_HELPER}/freefunc.c\
					${DIR_HELPER}/max.c\
					${DIR_HELPER}/openfile.c

OBJS		= ${SRC:.c=.o}

INCLUDE		= ./header

NAME	    = cub3d

AR			= ar rcs

# CC			= cc
CC			= cc -Wall -Wextra -Werror -g
  
LIBFT_DIR	= ./libft
LIBFT		= ${LIBFT_DIR}/libft.a

MINILIBX_DIR = ./minilibx-linux
LIBMLX 	= ${MINILIBX_DIR}/libmlx.a
LIBMLX_LINUX = ${MINILIBX_DIR}/libmlx_Linux.a

LFLAGS      =  -Lminilibx-linux -Lmlx-Linux -lX11 -lXext -lm

all: ${NAME}

%.o: %.c
			${CC} -c -I ${INCLUDE}  $< -o ${<:.c=.o} 

${NAME}: ${OBJS} ${LIBFT}
			$(MAKE) -C $(MINILIBX_DIR) all
			cc -g -o ${NAME} ${OBJS} ${LIBFT} ${LIBMLX} ${LIBMLX_LINUX} $(LFLAGS)	

${LIBFT}:
		make bonus -C ${LIBFT_DIR}

clean:
	make clean -C ${LIBFT_DIR}
	rm -f ${OBJS}

fclean: clean
	make fclean -C ${LIBFT_DIR}
	rm -f ${NAME}
	$(MAKE) -C $(MINILIBX_DIR) clean

re: fclean all

.PHONY: all clean fclean re

norm:
	norminette ./load ./gnl ./err 

test: ${NAME}
	./${NAME} maps/test.cub

t2: ${NAME}
	./${NAME} maps/works.cub

# testing all bad map
t0: ${NAME}
	for map in maps/bad/*; do echo -n "$$map" ": ";./cub3d "$$map";  done

# teseting all working map
t1: ${NAME}
	for map in maps/*.cub; do echo -n "$$map" ": ";./cub3d "$$map";echo "\n";  done