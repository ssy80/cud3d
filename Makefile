DIR			= .
DIR_ERR = ./err
DIR_HELPER = ./helper
DIR_LOAD = ./load
DIR_GNL = ./gnl
DIR_RAY_CAST = ./ray_casting
DIR_MOVEMENT = ./movement
DIR_EVENT = ./event
DIR_INIT = ./init
SRC			= 	${DIR}/cub3d.c \
				${DIR_INIT}/init.c \
				${DIR_INIT}/player_helper.c \
				${DIR_INIT}/player_helper2.c \
				${DIR_EVENT}/event_handler.c \
				${DIR_MOVEMENT}/movement.c \
				${DIR_MOVEMENT}/movement2.c \
				${DIR_RAY_CAST}/ray_casting.c \
				${DIR_RAY_CAST}/ray_casting2.c \
				${DIR_RAY_CAST}/ray_casting3.c \
				${DIR_RAY_CAST}/ray_casting4.c \
				${DIR_HELPER}/utils.c \
				${DIR_HELPER}/image_helper.c \
				${DIR_HELPER}/draw_helper.c \
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

HEADER      = ${INCLUDE}/cub3d.h

NAME	    = cub3D

AR			= ar rcs

CC			= cc -Wall -Wextra -Werror -g
  
LIBFT_DIR	= ./libft
LIBFT		= ${LIBFT_DIR}/libft.a

MINILIBX_DIR = ./minilibx-linux
LIBMLX 	= ${MINILIBX_DIR}/libmlx.a
LIBMLX_LINUX = ${MINILIBX_DIR}/libmlx_Linux.a

LFLAGS      =  -Lminilibx-linux -Lmlx-Linux -lX11 -lXext -lm

all: ${NAME}

%.o: %.c    ${HEADER}
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
	norminette ./load ./gnl ./err ./helper ./libft ./init ./ray_casting ./movement ./event ./header

test: ${NAME}
	./${NAME} maps/test.cub

t2: ${NAME}
	./${NAME} maps/works.cub

# testing all bad map
t0: ${NAME}
	for map in maps/bad/*; do echo -n "$$map" ": ";./cub3D "$$map";  done

# testing all working map
t1: ${NAME}
	for map in maps/*.cub; do echo -n "$$map" ": ";./cub3D "$$map";echo "\n";  done

leak: ${NAME}
	valgrind --leak-check=full ./cub3D maps/bad/color_missing_ceiling_rgb.cub